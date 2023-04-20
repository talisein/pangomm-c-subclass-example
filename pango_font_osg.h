#pragma once

#include <pango/pango-font.h>
#include <glib-object.h>

#include "pango_font_map_osg.h"

G_BEGIN_DECLS

/*
 * Type declaration.
 */
#define OSG_TYPE_FONT osg_font_get_type()
G_DECLARE_FINAL_TYPE (OsgFont, osg_font, OSG, FONT, PangoFont)

/*
 * Method definitions.
 */
OsgFont *osg_font_new (OsgFontMap *font_map, const PangoFontDescription *desc);

G_END_DECLS
