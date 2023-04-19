#pragma once

#include <pango/pango-renderer.h>
#include <glib-object.h>


G_BEGIN_DECLS

/*
 * Type declaration.
 */
#define OSG_TYPE_RENDERER osg_renderer_get_type()
#define OSG_RENDERER(object) (G_TYPE_CHECK_INSTANCE_CAST((object), OSG_TYPE_RENDERER, OsgRenderer))
#define OSG_IS_RENDERER(object) (G_TYPE_CHECK_INSTANCE_TYPE ((object), OSG_TYPE_RENDERER))

typedef struct _OsgRenderer OsgRenderer;

/*
 * Method definitions.
 */
OsgRenderer *osg_renderer_new (void);

G_END_DECLS
