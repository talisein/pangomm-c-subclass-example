#pragma once

#include <pango/pango-fontmap.h>
#include <glib-object.h>


G_BEGIN_DECLS

/*
 * Type declaration.
 */
#define OSG_TYPE_FONT_MAP osg_font_map_get_type()
G_DECLARE_FINAL_TYPE (OsgFontMap, osg_font_map, OSG, FONT_MAP, PangoFontMap)

/*
 * Method definitions.
 */
OsgFontMap *osg_font_map_new (void);

G_END_DECLS
