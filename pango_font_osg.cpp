#include <iostream>
#include "pango_font_osg.h"

struct OsgFontImpl
{

};

extern "C"
{

struct _OsgFont
{
  PangoFont parent_instance;

  /* Other members, including private data. */
  OsgFontImpl *pImpl;
  OsgFontMap *font_map;
  PangoFontDescription *desc;
};

G_DEFINE_TYPE (OsgFont, osg_font, PANGO_TYPE_FONT);

static void
finalize (GObject *object)
{
    OsgFont *osgfont = OSG_FONT(object);
    delete osgfont->pImpl;
    osgfont->pImpl = nullptr;
    if (osgfont->desc) pango_font_description_free(osgfont->desc);
    osgfont->desc = nullptr;

    PANGO_FONT_CLASS(osg_font_parent_class)->parent_class.finalize(object);
}

static PangoFontMetrics*
get_metrics (PangoFont* font, PangoLanguage* language)
{
    std::cout << "font get_metrics\n";
    return pango_font_get_metrics(NULL, language); // this function works when passed null
}

static void
get_glyph_extents (PangoFont* font, PangoGlyph glyph, PangoRectangle* ink_rect, PangoRectangle* logical_rect)
{
    std::cout << "font get_glyph_extents\n";
    pango_font_get_glyph_extents(NULL, glyph, ink_rect, logical_rect); // this function works when passed null
}

static PangoFontMap*
get_font_map (PangoFont* font)
{
    std::cout << "font get_font_map\n";
    return PANGO_FONT_MAP(OSG_FONT(font)->font_map);
}

static void
get_features (PangoFont* font, hb_feature_t* features, guint len, guint* num_features)
{
    std::cout << "font get_features\n";
    *num_features = 0;
}

static PangoCoverage*
get_coverage (PangoFont* font, PangoLanguage* language)
{
    std::cout << "font get_coverage\n";
    PangoCoverage *res = pango_coverage_new();
    return res;
}

static PangoFontDescription*
describe_absolute (PangoFont* font)
{
   std::cout << "font describe_absolute\n";
   return pango_font_description_copy(OSG_FONT(font)->desc);
}

static hb_font_t*
create_hb_font (PangoFont* font)
{
    std::cout << "create_hb_font\n";
    return hb_font_get_empty();
}

static void
osg_font_class_init (OsgFontClass *klass)
{
    PangoFontClass *font_class = PANGO_FONT_CLASS(klass);
    font_class->get_metrics = &get_metrics;
    font_class->get_glyph_extents = &get_glyph_extents;
    font_class->get_font_map = &get_font_map;
    font_class->get_features = &get_features;
    font_class->get_coverage = &get_coverage;
    font_class->describe_absolute = &describe_absolute;
    font_class->describe = &describe_absolute;
    font_class->create_hb_font = &create_hb_font;

    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    object_class->finalize = &finalize;
}

static void
osg_font_init (OsgFont *self)
{
//  ViewerFilePrivate *priv = viewer_file_get_instance_private (self);
  /* initialize all public and private members to reasonable default values.
   * They are all automatically initialized to 0 to begin with. */
  self->pImpl = new OsgFontImpl();
  self->desc = nullptr;
}

OsgFont *
osg_font_new (OsgFontMap *font_map, const PangoFontDescription *desc)
{
    OsgFont *font = OSG_FONT(g_object_new(OSG_TYPE_FONT, NULL));
    font->font_map = font_map;
    font->desc = pango_font_description_copy(desc);

    return font;
}

}
