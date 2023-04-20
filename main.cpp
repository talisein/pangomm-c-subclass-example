#include <pangomm.h>
#include <pangomm/init.h>
#include <glibmm/init.h>
#include "pango_font_map_osg.h"
#include "pango_renderer_osg.h"

int main(int argc, char *argv[])
{
    Glib::init();
    Pango::init();

    /* OsgFontMap is a PangoFontMap, so we can use the normal pangomm wrapping
       from the rest of the program.
       If OsgFontMap implements a new method you need to call, you can always
       osg_font_map_foo(font_map->gobj());
    */
    PangoFontMap* font_map = PANGO_FONT_MAP(osg_font_map_new());
    PangoContext *context = pango_context_new();
    pango_context_set_font_map(context, font_map);
    PangoLayout* layout = pango_layout_new(context);
    PangoRenderer* renderer = PANGO_RENDERER(osg_renderer_new());

    // Setting markup fails, I think because the font_map does not return a valid font.
    pango_layout_set_markup(layout, "example", 7);
    pango_renderer_draw_layout(renderer, layout, 0, 0);
    g_object_unref(renderer);
    g_object_unref(layout);
    g_object_unref(context);
    g_object_unref(font_map);
    return 0;

}
