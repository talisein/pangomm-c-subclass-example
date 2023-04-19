#include <map>
#include <iostream>
#include "pango_renderer_osg.h"

/* C++ implementation goes here */
struct OsgRendererImpl
{

    OsgRenderer *renderer; // For convenience if you need it

    OsgRendererImpl(OsgRenderer *renderer) : renderer(renderer) {
    }

    void draw_glyph (PangoFont* font, PangoGlyph glyph, double x, double y) {
        std::cout << "Drawing a glyph\n";
    }
    void draw_glyphs (PangoFont* font, PangoGlyphString *glyphs, double x, double y) {
        std::cout << "Drawing glyphs\n";
    }
    void draw_glyph_item (const char* text, PangoGlyphItem* glyph_item, int x, int y) {
        std::cout << "Drawing glyph item\n";
    }
    void draw_rectangle (PangoRenderPart part, int x, int y, int width, int height) {
        std::cout << "Rectangle\n";
    }
    void draw_trapezoid (PangoRenderPart part, double y1_, double x11, double x21, double y2, double x12, double x22) {
        std::cout << "Trapezoid\n";
    }
    void draw_error_underline (int x, int y, int width, int height) {
        std::cout << "Error underline\n";
    }
    void draw_shape (PangoAttrShape* attr, int x, int y) {
        std::cout << "Drawing shape\n";
    }

};

extern "C"
{

struct _OsgRenderer
{
  PangoRenderer parent_instance;

  /* Other members, including private data. */
  OsgRendererImpl *pImpl;
};

struct _OsgRendererClass
{
  PangoRendererClass parent_class;
};
typedef struct _OsgRendererClass OsgRendererClass;

#define OSG_RENDERER_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), OSG_TYPE_RENDERER, OsgRendererClass))

#define OSG_IS_RENDERER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), OSG_TYPE_RENDERER))

#define OSG_RENDERER_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), OSG_TYPE_RENDERER, OsgRendererClass))

G_DEFINE_TYPE (OsgRenderer, osg_renderer, PANGO_TYPE_RENDERER);

static void
finalize (GObject *object)
{
    OsgRenderer *osgrenderer = OSG_RENDERER(object);
    delete osgrenderer->pImpl;
    osgrenderer->pImpl = nullptr;
}

static void
draw_glyph (PangoRenderer* renderer, PangoFont* font, PangoGlyph glyph, double x, double y)
{
    OsgRenderer *osgrenderer = OSG_RENDERER(renderer);
    osgrenderer->pImpl->draw_glyph(font, glyph, x, y);
}

static void
draw_glyphs (PangoRenderer* renderer, PangoFont* font, PangoGlyphString* glyphs, int x, int y) {
    OsgRenderer *osgrenderer = OSG_RENDERER(renderer);
    osgrenderer->pImpl->draw_glyphs(font, glyphs, x, y);
}

static void
draw_glyph_item (PangoRenderer* renderer, const char* text, PangoGlyphItem* glyph_item, int x, int y) {
    OsgRenderer *osgrenderer = OSG_RENDERER(renderer);
    osgrenderer->pImpl->draw_glyph_item(text, glyph_item, x, y);
}

static void
draw_rectangle (PangoRenderer* renderer, PangoRenderPart part, int x, int y, int width, int height) {
    OsgRenderer *osgrenderer = OSG_RENDERER(renderer);
    osgrenderer->pImpl->draw_rectangle(part, x, y, width, height);
}

static void
draw_trapezoid (PangoRenderer* renderer, PangoRenderPart part, double y1_, double x11, double x21, double y2, double x12, double x22) {
    OsgRenderer *osgrenderer = OSG_RENDERER(renderer);
    osgrenderer->pImpl->draw_trapezoid(part, y1_, x11, x21, y2, x12, x22);
}

static void
draw_error_underline (PangoRenderer* renderer, int x, int y, int width, int height) {
    OsgRenderer *osgrenderer = OSG_RENDERER(renderer);
    osgrenderer->pImpl->draw_error_underline(x, y, width, height);
}

static void
draw_shape (PangoRenderer* renderer, PangoAttrShape* attr, int x, int y)
{
    OsgRenderer *osgrenderer = OSG_RENDERER(renderer);
    osgrenderer->pImpl->draw_shape(attr, x, y);
}


static void
osg_renderer_class_init (OsgRendererClass *klass)
{
    PangoRendererClass *renderer_class = PANGO_RENDERER_CLASS(klass);
    renderer_class->draw_glyph = &draw_glyph;
    renderer_class->draw_glyphs = &draw_glyphs;
    renderer_class->draw_glyph_item = &draw_glyph_item;
    renderer_class->draw_rectangle = &draw_rectangle;
    renderer_class->draw_trapezoid = &draw_trapezoid;
    renderer_class->draw_error_underline = &draw_error_underline;
    renderer_class->draw_shape = &draw_shape;

    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    object_class->finalize = &finalize;
}

static void
osg_renderer_init (OsgRenderer *self)
{
//  ViewerFilePrivate *priv = viewer_file_get_instance_private (self);
  /* initialize all public and private members to reasonable default values.
   * They are all automatically initialized to 0 to begin with. */
  self->pImpl = new OsgRendererImpl(self);
}

OsgRenderer *
osg_renderer_new (void)
{
    return OSG_RENDERER(g_object_new(OSG_TYPE_RENDERER, NULL));
}

} // extern "C"
