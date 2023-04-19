#include <map>
#include <iostream>
#include "pango_font_map_osg.h"

/* C++ implementation goes here */
struct OsgFontMapImpl
{
    std::map<int, int> x;

    void list_families (PangoFontFamily*** families, int* n_families) {
        std::cout << "list_families\n";
        *n_families = 0;
        *families = nullptr;
    }

    PangoFont*
    load_font (PangoContext* context, const PangoFontDescription* desc) {
        std::cout << "load_font\n";
        return nullptr;
    }

    PangoFontset* load_fontset (PangoContext* context,
                                const PangoFontDescription* desc,
                                PangoLanguage* language) {
        std::cout << "load_fontset\n";
        return nullptr;
    }
};

extern "C"
{

struct _OsgFontMap
{
  GObject parent_instance;

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
  self->pImpl = new OsgFontMapImpl();
}

OsgFontMap *
osg_font_map_new (void)
{
    return OSG_FONT_MAP(g_object_new(OSG_TYPE_FONT_MAP, NULL));
}

} // extern "C"
