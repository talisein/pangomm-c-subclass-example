#include <pangomm.h>
#include <pangomm/init.h>
#include <glibmm/init.h>
#include "pango_font_map_osg.h"

int main(int argc, char *argv[])
{
    Glib::init();
    Pango::init();

    /* OsgFontMap is a PangoFontMap, so we can use the normal pangomm wrapping
       from the rest of the program. */
    Glib::RefPtr<Pango::FontMap> font_map = Glib::wrap(PANGO_FONT_MAP(osg_font_map_new()));
    Glib::RefPtr<Pango::Context> context = font_map->create_context();
    Glib::RefPtr<Pango::Layout> layout = Pango::Layout::create(context);
    layout->set_markup("example");

    return 0;

}
