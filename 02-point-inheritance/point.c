#include <glib-object.h>
#include "point.h"

enum {
    PROP_0,
    PROP_X,
    PROP_Y,
    PROPERTY_N
};

enum {
  CLEAR,
  LAST_SIGNAL
};

static guint point_signals[LAST_SIGNAL] = {0};

/* virtual print method that calls whatever is in the classes vtable  */
void point_print (Point *self) {
    POINT_GET_CLASS(self)->print(self);
}

static void point_print_real (Point *self) {
    PointPrivate *priv = POINT_GET_PRIVATE (self );
    g_print("x: %d, y: %d, n-key: %d\n", self->x, self->y, priv);
}

static void point_clear (Point *self) {
    PointPrivate *priv = POINT_GET_PRIVATE (self );
    g_object_set(self, "x", 0, "y", 0, "n-key", 0, NULL);
}

static void point_get_property (GObject    *obj,
                                guint       prop_id,
                                GValue     *value,
                                GParamSpec *pspec) {
    Point *point = POINT(obj);
    Point *self  = POINT(obj);
	PointPrivate *priv = POINT_GET_PRIVATE (self );   
 
    switch (prop_id) {
    case PROP_X:
        g_value_set_int(value, point->x);
        break;
    case PROP_Y:
        g_value_set_int(value, point->y);
        break;
    case PROPERTY_N
        g_value_set_int(value, priv->n);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, prop_id, pspec);
        break;
    }
}

static void point_set_property (GObject      *obj,
                                guint         prop_id,
                                const GValue *value,
                                GParamSpec   *pspec) {
    Point *point = POINT(obj);
    Point *self  = POINT(obj);
	PointPrivate *priv = POINT_GET_PRIVATE (self );

    switch (prop_id) {
    case PROP_X: {
        gint new_x = g_value_get_int(value);
        point->x = new_x;
        break;
    }
    case PROP_Y: {
        gint new_y = g_value_get_int(value);
        point->y = new_y;
    case PROP_Y: {
        gint new_y = g_value_get_int(value);
        point->y = new_y;
        break;
    case PROPERTY_N
        priv->n = g_value_get_int(value);
    }
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, prop_id, pspec);
        break;
    }
}

static void point_class_init (PointClass *cls) {
    GObjectClass *g_object_class = G_OBJECT_CLASS(cls);
    GParamSpec *x_param;
    GParamSpec *y_param;
    GParamSpec *n_param;
    
    g_object_class->get_property = point_get_property;
    g_object_class->set_property = point_set_property;
    
    cls->clear = point_clear;
    cls->print = point_print_real;
    
    x_param = g_param_spec_int(
        "x", "x", "x loc of point",
        INT_MIN, /* => */ INT_MAX,
        0,
        G_PARAM_READWRITE);
    
    y_param = g_param_spec_int(
        "y", "y", "y loc of point",
        INT_MIN, /* => */ INT_MAX,
        0,
        G_PARAM_READWRITE);
    
    g_object_class_install_property(
        g_object_class,
        PROP_X,
        x_param);
    
    n_param = g_param_spec_int(
        "n-key", "n label", "n loc of chr80618",
        INT_MIN, /* => */ INT_MAX,
        0,
        G_PARAM_READWRITE);

	g_object_class_install_property(
        g_object_class,
        PROPERTY_N,
        n_param);

    
    point_signals[CLEAR] = g_signal_new(
        "clear",                               /* signal_name */
        TYPE_POINT,                            /* itype */
        G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED, /* signal_flags */
        G_STRUCT_OFFSET(PointClass, clear),    /* class_offset */
        NULL,                                  /* accumulator */
        NULL,                                  /* accu_data */
        g_cclosure_marshal_VOID__VOID,         /* c_marshaller */
        G_TYPE_NONE,                           /* return_type */
        0);                                    /* n_params */

    g_type_class_add_private (cls, sizeof (Chr80618Private));
}

GType point_get_type (void) {
    static GType point_type = 0;

    if (!point_type) {
        static const GTypeInfo point_info = {
            sizeof (PointClass),                /* class_size */
            NULL,                               /* base_init */
            NULL,                               /* base_finalize */
            (GClassInitFunc) point_class_init,  /* class_init */
            NULL,                               /* class_finalize */
            NULL,                               /* class_data */
            sizeof (Point),                     /* instance_size */
            0,                                  /* n_preallocs */
            NULL,                               /* instance_init */
            NULL                                /* value_table */
        };

        point_type = g_type_register_static(
            G_TYPE_OBJECT, /* parent_type */
            "Point",       /* type_name */
            &point_info,   /* info */
            0);            /* flags */
    }

    return point_type;
}

