#include <map>
#include <iostream>
#include "pango_font_map_osg.h"

/* C++ implementation goes here */
struct OsgFontMapImpl
{
    std::map<int, int> my_map;
    OsgFontMap *font_map; // For convenience if you need it

    OsgFontMapImpl(OsgFontMap *font_map) : font_map(font_map) {
        // populate my_map etc.
    }

    PangoFontFamily *get_pango_font_family_from_my_map(decltype(my_map)::iterator &it) {
        // however you want to implement this
        return nullptr;
    }

    /* The contract here is that the returned families will be freed with
     * g_free */
    void list_families (PangoFontFamily*** families, int* n_families) {
        std::cout << "list_families\n";
        PangoFontFamily **list = (PangoFontFamily**)g_malloc(sizeof(PangoFontFamily*) * my_map.size());
        PangoFontFamily **end = list + my_map.size();
        auto my_map_iter = my_map.begin();
        for (PangoFontFamily **iter = list; iter < end; ++iter, ++my_map_iter) {
            *iter = get_pango_font_family_from_my_map(my_map_iter);
        }

        *n_families = my_map.size();
        *families = list;
    }

    PangoFont*
    load_font (PangoContext* c_context, const PangoFontDescription* c_desc) {
        auto str = pango_font_description_to_string(c_desc);
        std::cout << "load_font " << str << '\n';
        g_free(str);
        return nullptr;
    }

    PangoFontset* load_fontset (PangoContext* c_context,
                                const PangoFontDescription* c_desc,
                                PangoLanguage* c_language) {
        char *str = pango_font_description_to_string(c_desc);
        const char* lang = pango_language_to_string(c_language);
        std::cout << "load_fontset " << str << " " << lang << '\n';
        g_free(str);
        return nullptr;
    }
};

extern "C"
{

struct _OsgFontMap
{
  PangoFontMap parent_instance;

  /* Other members, including private data. */
  OsgFontMapImpl *pImpl;
};

G_DEFINE_TYPE (OsgFontMap, osg_font_map, PANGO_TYPE_FONT_MAP);

static void
finalize (GObject *object)
{
    OsgFontMap *osgfontmap = OSG_FONT_MAP(object);
    delete osgfontmap->pImpl;
    osgfontmap->pImpl = nullptr;
    PANGO_FONT_MAP_CLASS(osg_font_map_parent_class)->parent_class.finalize(object);
}

static void
list_families (
  PangoFontMap* fontmap,
  PangoFontFamily*** families,
  int* n_families
)
{
    OsgFontMap *osgfontmap = OSG_FONT_MAP(fontmap);
    osgfontmap->pImpl->list_families(families, n_families);
}

static PangoFont*
load_font (
  PangoFontMap* fontmap,
  PangoContext* context,
  const PangoFontDescription* desc
)
{
    OsgFontMap *osgfontmap = OSG_FONT_MAP(fontmap);
    return osgfontmap->pImpl->load_font(context, desc);
}

static PangoFontset*
load_fontset (
  PangoFontMap* fontmap,
  PangoContext* context,
  const PangoFontDescription* desc,
  PangoLanguage* language
)
{
    OsgFontMap *osgfontmap = OSG_FONT_MAP(fontmap);
    return osgfontmap->pImpl->load_fontset(context, desc, language);
}

static void
osg_font_map_class_init (OsgFontMapClass *klass)
{
    PangoFontMapClass *font_map_class = PANGO_FONT_MAP_CLASS(klass);

	font_map_class->list_families = &list_families;
	font_map_class->load_font = &load_font;
	font_map_class->load_fontset = &load_fontset;
	font_map_class->shape_engine_type = "PangoRendererCanvas";

    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    object_class->finalize = &finalize;
}

static void
osg_font_map_init (OsgFontMap *self)
{
//  ViewerFilePrivate *priv = viewer_file_get_instance_private (self);
  /* initialize all public and private members to reasonable default values.
   * They are all automatically initialized to 0 to begin with. */
  self->pImpl = new OsgFontMapImpl(self);
}

OsgFontMap *
osg_font_map_new (void)
{
    return OSG_FONT_MAP(g_object_new(OSG_TYPE_FONT_MAP, NULL));
}

} // extern "C"
