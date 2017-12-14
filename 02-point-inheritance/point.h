#ifndef __POINT_H__
#define __POINT_H__

#include <glib-object.h>

typedef struct _PointClass PointClass;
typedef struct _Point      Point;
typedef struct _pointPrivate 	PointPrivate;

struct _pointPrivate
{
    guint n;
};

struct _PointClass {
    GObjectClass parent;
    void (*clear) (Point *self);
    void (*print) (Point *self);
};

struct _Point {
    GObject  parent;
    gint     x;
    gint     y;
};

#define TYPE_POINT           (point_get_type             ())
#define POINT(obj)           (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_POINT, Point))
#define POINT_CLASS(cls)     (G_TYPE_CHECK_CLASS_CAST    ((cls), TYPE_POINT, PointClass))
#define IS_POINT(obj)        (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_POINT))
#define IS_POINT_CLASS(cls)  (G_TYPE_CHECK_CLASS_TYPE    ((cls), TYPE_POINT))
#define POINT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS  ((obj), TYPE_POINT, PointClass))
#define POINT_GET_PRIVATE(obj) 	(G_TYPE_INSTANCE_GET_PRIVATE((obj), TYPE_POINT, PointPrivate))

GType  point_get_type  (void);
void   point_print     (Point *self);

#endif
