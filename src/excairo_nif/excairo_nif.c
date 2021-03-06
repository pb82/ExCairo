#include "./include/excairo_nif.h"

/**
 * Those predefined atoms are used in places where c enums are passed.
 * Enums could be represented as integers, but using atoms makes for a
 * nicer API on the erlang/elixir side.
 * @brief init_terms
 * @param env
 */
static void define_predef_atoms (ErlNifEnv *env) {
    ET_invalid          = enif_make_atom(env, "invalid");
    ET_a1               = enif_make_atom(env, "a1");
    ET_a8               = enif_make_atom(env, "a8");
    ET_argb32           = enif_make_atom(env, "argb32");
    ET_rgb16_565        = enif_make_atom(env, "rgb16_565");
    ET_rgb24            = enif_make_atom(env, "rgb24");
    ET_rgb30            = enif_make_atom(env, "rgb30");
    ET_normal           = enif_make_atom(env, "normal");
    ET_italic           = enif_make_atom(env, "italic");
    ET_oblique          = enif_make_atom(env, "oblique");
    ET_bold             = enif_make_atom(env, "bold");
    ET_butt             = enif_make_atom(env, "butt");
    ET_round            = enif_make_atom(env, "round");
    ET_square           = enif_make_atom(env, "square");
    ET_miter            = enif_make_atom(env, "miter");
    ET_bevel            = enif_make_atom(env, "bevel");

    ET_clear            = enif_make_atom(env, "clear");
    ET_source           = enif_make_atom(env, "source");
    ET_over             = enif_make_atom(env, "over");
    ET_in               = enif_make_atom(env, "in");
    ET_out              = enif_make_atom(env, "out");
    ET_atop             = enif_make_atom(env, "atop");
    ET_dest             = enif_make_atom(env, "dest");
    ET_dest_over        = enif_make_atom(env, "dest_over");
    ET_dest_in          = enif_make_atom(env, "dest_in");
    ET_dest_out         = enif_make_atom(env, "dest_out");
    ET_dest_atop        = enif_make_atom(env, "dest_atop");
    ET_xor              = enif_make_atom(env, "xor");
    ET_add              = enif_make_atom(env, "add");
    ET_saturate         = enif_make_atom(env, "saturate");
    ET_multiply         = enif_make_atom(env, "multiply");
    ET_screen           = enif_make_atom(env, "screen");
    ET_overlay          = enif_make_atom(env, "overlay");
    ET_darken           = enif_make_atom(env, "darken");
    ET_lighten          = enif_make_atom(env, "lighten");
    ET_color_dodge      = enif_make_atom(env, "color_dodge");
    ET_color_burn       = enif_make_atom(env, "color_burn");
    ET_hard_light       = enif_make_atom(env, "hard_light");
    ET_soft_light       = enif_make_atom(env, "soft_light");
    ET_difference       = enif_make_atom(env, "difference");
    ET_exclusion        = enif_make_atom(env, "exclusion");
    ET_hsl_hue          = enif_make_atom(env, "hsl_hue");
    ET_hsl_saturation   = enif_make_atom(env, "hsl_saturation");
    ET_hsl_color        = enif_make_atom(env, "hsl_color");
    ET_hsl_luminosity   = enif_make_atom(env, "hsl_luminosity");

    ET_none             = enif_make_atom(env, "none");
    ET_repeat           = enif_make_atom(env, "repeat");
    ET_reflect          = enif_make_atom(env, "reflect");
    ET_pad              = enif_make_atom(env, "pad");

    ET_fast             = enif_make_atom(env, "fast");
    ET_good             = enif_make_atom(env, "good");
    ET_best             = enif_make_atom(env, "best");
    ET_nearest          = enif_make_atom(env, "nearest");
    ET_bilinear         = enif_make_atom(env, "bilinear");
    ET_gaussian         = enif_make_atom(env, "gaussian");

    ET_color            = enif_make_atom(env, "color");
    ET_alpha            = enif_make_atom(env, "alpha");
    ET_color_alpha      = enif_make_atom(env, "color_alpha");
}

/**
 * NIF initialization
 * @brief load
 * @param env Erlang environment
 * @param priv
 * @param load_info The argument passed from the init function
 * @return 0 on success, -1 otherwise
 */
static int load(ErlNifEnv *env, void **priv, ERL_NIF_TERM load_info) {
    ERL_ASSERT_LOAD(env);
    ERL_ASSERT_LOAD(priv);

    // Get the parameter passed from the init function
    // in Elixir
    int parameter;
    if(!enif_get_int(env, load_info, &parameter)) {
        return enif_make_badarg(env);
    }

    // Enforce the init parameter to be zero
    ERL_ASSERT(parameter == 0);

    // Define cairo_surface_t_TYPE
    cairo_surface_t_RT = enif_open_resource_type(
             env,
             NULL,
             "cairo_surface_t_TYPE",
             gc_cairo_surface_t,
             ERL_NIF_RT_CREATE, NULL);

    // Define cairo_path_t_TYPE
    cairo_path_t_RT = enif_open_resource_type(
             env,
             NULL,
             "cairo_path_t_TYPE",
             gc_cairo_path_t,
             ERL_NIF_RT_CREATE, NULL);

    // Define cairo_font_face_t_TYPE
    cairo_font_face_t_RT = enif_open_resource_type(
             env,
             NULL,
             "cairo_font_face_t_TYPE",
             gc_cairo_font_face_t,
             ERL_NIF_RT_CREATE, NULL);

    // Define cairo_font_options_t_TYPE
    cairo_font_options_t_RT = enif_open_resource_type(
             env,
             NULL,
             "cairo_font_options_t_TYPE",
             gc_cairo_font_options_t,
             ERL_NIF_RT_CREATE, NULL);

    // Define cairo_pattern_t_TYPE
    cairo_pattern_t_RT = enif_open_resource_type(
             env,
             NULL,
             "cairo_pattern_t_TYPE",
             gc_cairo_pattern_t,
             ERL_NIF_RT_CREATE, NULL);

    // Define cairo_region_t_TYPE
    cairo_region_t_RT = enif_open_resource_type(
             env,
             NULL,
             "cairo_region_t_TYPE",
             gc_cairo_region_t,
             ERL_NIF_RT_CREATE, NULL);

    // Define cairo_t_TYPE
    cairo_t_RT = enif_open_resource_type(
             env,
             NULL,
             "cairo_t_TYPE",
             gc_cairo_t,
             ERL_NIF_RT_CREATE, NULL);

    // Assert that all definitions were successful
    ERL_ASSERT_LOAD(cairo_surface_t_RT);
    ERL_ASSERT_LOAD(cairo_path_t_RT);
    ERL_ASSERT_LOAD(cairo_font_face_t_RT);
    ERL_ASSERT_LOAD(cairo_font_options_t_RT);
    ERL_ASSERT_LOAD(cairo_pattern_t_RT);
    ERL_ASSERT_LOAD(cairo_region_t_RT);
    ERL_ASSERT_LOAD(cairo_t_RT);

    // Initialize the predefined erlang terms
    define_predef_atoms(env);

    // Return success
    return 0;
}

/**
 * Wraps cairo_arc(cairo_t *cr, double xc, double yc, double radius, double angle1, double angle2)
 * @brief EX_arc
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_arc(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(6);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    double xc, yc, radius, angle1, angle2;
    enif_get_double(env, argv[1], &xc);
    enif_get_double(env, argv[2], &yc);
    enif_get_double(env, argv[3], &radius);
    enif_get_double(env, argv[4], &angle1);
    enif_get_double(env, argv[5], &angle2);

    cairo_arc(context->data, xc, yc, radius, angle1, angle2);
    return ERL_OK;
}

/**
 * Wraps cairo_arc_negative(cairo_t *cr, double xc, double yc, double radius, double angle1, double angle2)
 * @brief EX_arc
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_arc_negative(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(6);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    double xc, yc, radius, angle1, angle2;
    enif_get_double(env, argv[1], &xc);
    enif_get_double(env, argv[2], &yc);
    enif_get_double(env, argv[3], &radius);
    enif_get_double(env, argv[4], &angle1);
    enif_get_double(env, argv[5], &angle2);

    cairo_arc_negative(context->data, xc, yc, radius, angle1, angle2);
    return ERL_OK;
}

/**
 * Wraps cairo_clip(caior_t *cr)
 * @brief EX_clip
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_clip(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    cairo_clip(context->data);

    return ERL_OK;
}

/**
 * Wraps cairo_clip_extents(caior_t *cr, double *x1, double *y1, double *x2, double *y2)
 * -> returns a 4-tuple containint the coordinates, since they might have been modified by
 * cairo_clip_extents
 * @brief EX_clip_extents
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_clip_extents(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(5);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    double x1, y1, x2, y2;
    enif_get_double(env, argv[1], &x1);
    enif_get_double(env, argv[2], &y1);
    enif_get_double(env, argv[3], &x2);
    enif_get_double(env, argv[4], &y1);

    cairo_clip_extents(context->data, &x1, &y1, &x2, &y2);

    return enif_make_tuple4(env,
                            enif_make_double(env, x1),
                            enif_make_double(env, y1),
                            enif_make_double(env, x2),
                            enif_make_double(env, y2));
}

/**
 * Wraps cairo_clip_preserve(caior_t *cr)
 * @brief EX_clip_preserve
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_clip_preserve(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    cairo_clip_preserve(context->data);

    return ERL_OK;
}

/**
 * Wraps cairo_close_path(caior_t *cr)
 * @brief EX_close_path
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_close_path(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    cairo_close_path(context->data);

    return ERL_OK;
}

/**
 * Wrapw cairo_copy_clip_rectangle_list(cairo_t *cr)
 * -> Returns an array of tuples where each tuple contains the coordinates and dimensions
 * of a single rectangle
 * @brief EX_clip_rectangle_list
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_copy_clip_rectangle_list(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    cairo_rectangle_list_t *rects = cairo_copy_clip_rectangle_list(context->data);
    /**
      * Iterate through all rectangles that the call returned.
      * The number of rectangles is contained in the returned
      * structure.
      */
    if (rects->status == CAIRO_STATUS_SUCCESS && rects->num_rectangles) {
        /**
         * The function returns a list of tuples where each tuple holds
         * one rectangle (x, y, w, h)
         * @brief rect_tuples
         */
        ERL_NIF_TERM rect_tuples[rects->num_rectangles];

        int i;
        for (i = 0; i < rects->num_rectangles; i++) {
            cairo_rectangle_t rect = rects->rectangles[i];
            rect_tuples[i] = enif_make_tuple4(env,
                                              enif_make_double(env, rect.x),
                                              enif_make_double(env, rect.y),
                                              enif_make_double(env, rect.width),
                                              enif_make_double(env, rect.height));
        }

        // Return a list, created from the tuple array
        return enif_make_list_from_array(env, rect_tuples, rects->num_rectangles);
    } else {
        /**
          * If the number of rectangles is zero or the call returned
          * with a failure, an empty list is returned.
          *
          * TODO: return failure status to user
          */
        return enif_make_list(env, 0);
    }
}

/**
 * Wraps cairo_copy_page(caior_t *cr)
 * @brief EX_copy_page
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_copy_page(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    cairo_copy_page(context->data);

    return ERL_OK;
}

/**
 * Wraps cairo_copy_path(caior_t *cr)
 * @brief EX_copy_path
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_copy_path(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    ERL_MAKE_INSTANCE(cairo_path_t_TYPE, cairo_path_t_RT, instance);
    ERL_ASSERT(instance);

    instance->data = cairo_copy_path(context->data);

    // Create a garbage-collectable resource
    ERL_MAKE_GC_RES(instance, path);
    return ERL_MAKE_OK_TUPLE(path);
}

/**
 * Wraps cairo_copy_path_flat(caior_t *cr)
 * @brief EX_copy_path_flat
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_copy_path_flat(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    ERL_MAKE_INSTANCE(cairo_path_t_TYPE, cairo_path_t_RT, instance);
    ERL_ASSERT(instance);

    instance->data = cairo_copy_path_flat(context->data);

    // Create a garbage-collectable resource
    ERL_MAKE_GC_RES(instance, path);
    return ERL_MAKE_OK_TUPLE(path);
}

/**
 * Wraps cairo_curve_to(
 *  caior_t *cr,
 *  double x1,
 *  double y1,
 *  double x2,
 *  double y2,
 *  double x3,
 *  double y3)
 * @brief EX_curve_to
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_curve_to(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(7);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    double x1, y1, x2, y2, x3, y3;
    enif_get_double(env, argv[1], &x1);
    enif_get_double(env, argv[2], &y1);
    enif_get_double(env, argv[3], &x2);
    enif_get_double(env, argv[4], &y2);
    enif_get_double(env, argv[5], &x3);
    enif_get_double(env, argv[6], &y3);

    cairo_curve_to(context->data, x1, y1, x2, y2, x3, y3);

    return ERL_OK;
}

// TODO (?)
// Devices

/**
 * Wraps cairo_fill(caior_t *cr)
 * @brief EX_fill
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_fill(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    cairo_fill(context->data);

    return ERL_OK;
}

/**
 * Wraps cairo_fill_extents(caior_t *cr, double *x1, double *y1, double *x2, double *y2)
 * -> Returns a 4-tuple containing the coordinates since cairo_fill_extents may
 * modify them
 * @brief EX_fill_extents
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_fill_extents(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    double x1, y1, x2, y2;
    enif_get_double(env, argv[1], &x1);
    enif_get_double(env, argv[2], &y1);
    enif_get_double(env, argv[3], &x2);
    enif_get_double(env, argv[4], &y2);

    return enif_make_tuple4(env,
                enif_make_double(env, x1),
                enif_make_double(env, y1),
                enif_make_double(env, x2),
                enif_make_double(env, y2));
}


/**
 * Wraps cairo_fill_preserve(caior_t *cr)
 * @brief EX_fill_preserve
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_fill_preserve(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    cairo_fill_preserve(context->data);

    return ERL_OK;
}

/**
 * Wraps cairo_font_extents(caior_t *cr, cairo_font_extents_t *extents)
 * -> Returns a 5-tuple containing the members of the cairo_font_extents_t
 * struct.
 * @brief EX_font_extents
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_font_extents(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    cairo_font_extents_t font_extents;
    cairo_font_extents(context->data, &font_extents);

    return enif_make_tuple5(env,
                            enif_make_double(env, font_extents.ascent),
                            enif_make_double(env, font_extents.descent),
                            enif_make_double(env, font_extents.height),
                            enif_make_double(env, font_extents.max_x_advance),
                            enif_make_double(env, font_extents.max_y_advance));
}

// TODO
// Font functions
// (cairo_font...)
// cairo_format_stride_for_width

/**
 * Wraps cairo_get_antialias(caior_t *cr)
 * @brief EX_get_antialias
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_get_antialias(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    cairo_antialias_t antialias = cairo_get_antialias(context->data);
    switch(antialias) {
    case CAIRO_ANTIALIAS_DEFAULT:
        return enif_make_atom(env, "default");
    case CAIRO_ANTIALIAS_NONE:
        return enif_make_atom(env, "none");
    case CAIRO_ANTIALIAS_GRAY:
        return enif_make_atom(env, "gray");
    case CAIRO_ANTIALIAS_SUBPIXEL:
        return enif_make_atom(env, "subpixel");
    case CAIRO_ANTIALIAS_FAST:
        return enif_make_atom(env, "fast");
    case CAIRO_ANTIALIAS_GOOD:
        return enif_make_atom(env, "good");
    case CAIRO_ANTIALIAS_BEST:
        return enif_make_atom(env, "best");
    default:
        return enif_make_badarg(env);
    }
}

/**
 * Wraps cairo_get_current_point(caior_t *cr, double *x, double *y)
 * -> Returns a 2-tuple containing the coordinates of the point (x,y)
 * @brief EX_get_current_point
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_get_current_point(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    double x, y;
    cairo_get_current_point(context->data, &x, &y);
    return enif_make_tuple2(env,
                            enif_make_double(env, x),
                            enif_make_double(env, y));
}

/**
 * Wraps cairo_get_dash(caior_t *cr, double *dashes, double *offset)
 * -> Returns a 2-tuple containing the data (dashes,offset)
 * @brief EX_get_dash
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_get_dash(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    double dashes, offset;
    cairo_get_current_point(context->data, &dashes, &offset);
    return enif_make_tuple2(env,
                            enif_make_double(env, dashes),
                            enif_make_double(env, offset));
}

/**
 * Wraps cairo_get_dash_count(caior_t *cr)
 * -> Returns an integer (dash count)
 * @brief EX_get_dash_count
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_get_dash_count(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    int dash_count = cairo_get_dash_count(context->data);
    return enif_make_int(env, dash_count);
}

/**
 * Wraps cairo_get_fill_rule(caior_t *cr)
 * -> Returns an integer (fill rule)
 * @brief EX_get_dash_count
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_get_fill_rule(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    cairo_fill_rule_t rule = cairo_get_fill_rule(context->data);
    switch (rule) {
    case CAIRO_FILL_RULE_WINDING:
        return enif_make_atom(env, "winding");
    case CAIRO_FILL_RULE_EVEN_ODD:
        return enif_make_atom(env, "even_odd");
    default:
        return enif_make_badarg(env);
    }
}

/**
 * Wraps cairo_get_font_face(caior_t *cr)
 * @brief EX_get_font_face
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_get_font_face(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    ERL_MAKE_INSTANCE(cairo_font_face_t_TYPE, cairo_font_face_t_RT, instance);
    ERL_ASSERT(instance);

    instance->data = cairo_get_font_face(context->data);

    // Create a garbage-collectable resource
    ERL_MAKE_GC_RES(instance, font_face);
    return ERL_MAKE_OK_TUPLE(font_face);
}

/**
 * Wraps cairo_get_font_matrix
 * -> Returns a list of tuples, representing the matrix
 * @brief EX_get_dash_count
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_get_font_matrix(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    cairo_matrix_t matrix;
    cairo_get_font_matrix(context->data, &matrix);

    return ERL_EXPORT_MATRIX(matrix);
}

/**
 * Wraps cairo_get_font_options(cairo_t *cr, cairo_font_options_t *options)
 * -> Retruns a resource containing a font options object
 * @brief EX_get_font_options
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_get_font_options(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    ERL_MAKE_INSTANCE(cairo_font_options_t_TYPE, cairo_font_options_t_RT, instance);
    ERL_ASSERT(instance);

    cairo_get_font_options(context->data, instance->data);

    // Create a garbage-collectable resource
    ERL_MAKE_GC_RES(instance, opts);
    return opts;
}



/**
 * Wraps cairo_get_group_target(cairo_t *cr)
 * -> Returns a non-garbage collectable pointer to a surface
 * @brief EX_get_font_options
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_get_group_target(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    ERL_MAKE_INSTANCE(cairo_surface_t_TYPE, cairo_surface_t_RT, instance);
    ERL_ASSERT(instance);

    // Must not be garbage collected since this instance
    // is owned by cairo
    instance->data = cairo_get_group_target(context->data);

    return enif_make_resource(env, instance);
}

/**
 * Wraps cairo_get_line_cap(cairo_t *cr)
 * @brief EX_get_line_cap
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_get_line_cap(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    cairo_line_cap_t cap = cairo_get_line_cap(context->data);
    switch (cap) {
    case CAIRO_LINE_CAP_BUTT:
        return enif_make_atom(env, "butt");
    case CAIRO_LINE_CAP_ROUND:
        return enif_make_atom(env, "round");
    case CAIRO_LINE_CAP_SQUARE:
        return enif_make_atom(env, "square");
    default:
        return enif_make_badarg(env);
    }
}

/**
 * Wraps cairo_get_line_join(cairo_t *cr)
 * @brief EX_get_line_join
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_get_line_join(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    cairo_line_join_t join = cairo_get_line_join(context->data);
    switch (join) {
    case CAIRO_LINE_JOIN_MITER:
        return enif_make_atom(env, "miter");
    case CAIRO_LINE_JOIN_ROUND:
        return enif_make_atom(env, "round");
    case CAIRO_LINE_JOIN_BEVEL:
        return enif_make_atom(env, "bevel");
    default:
        return enif_make_badarg(env);
    }
}

/**
 * Wraps cairo_get_line_width(cairo_t *cr)
 * @brief EX_get_line_width
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_get_line_width(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    double width = cairo_get_line_width(context->data);
    return enif_make_double(env, width);
}

/**
 * Wraps cairo_get_matrix(cairo_t *cr)
 * @brief EX_get_matrix
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_get_matrix(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    cairo_matrix_t matrix;
    cairo_get_matrix(context->data, &matrix);

    return ERL_EXPORT_MATRIX(matrix);
}

/**
 * Wraps cairo_get_miter_limit(cairo_t *cr)
 * @brief EX_get_miter_limit
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_get_miter_limit(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    double limit = cairo_get_miter_limit(context->data);
    return enif_make_double(env, limit);
}

/**
 * Wraps cairo_get_operator(cairo_t *cr)
 * @brief EX_get_operator
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_get_operator(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    cairo_operator_t op = cairo_get_operator(context->data);
    switch(op) {
    case CAIRO_OPERATOR_CLEAR:
        return enif_make_atom(env, "clear");
    case CAIRO_OPERATOR_SOURCE:
        return enif_make_atom(env, "source");
    case CAIRO_OPERATOR_OVER:
        return enif_make_atom(env, "over");
    case CAIRO_OPERATOR_IN:
        return enif_make_atom(env, "in");
    case CAIRO_OPERATOR_OUT:
        return enif_make_atom(env, "out");
    case CAIRO_OPERATOR_ATOP:
        return enif_make_atom(env, "atop");
    case CAIRO_OPERATOR_DEST:
        return enif_make_atom(env, "dest");
    case CAIRO_OPERATOR_DEST_OVER:
        return enif_make_atom(env, "over");
    case CAIRO_OPERATOR_DEST_IN:
        return enif_make_atom(env, "dest_in");
    case CAIRO_OPERATOR_DEST_OUT:
        return enif_make_atom(env, "dest_out");
    case CAIRO_OPERATOR_DEST_ATOP:
        return enif_make_atom(env, "dest_atop");
    case CAIRO_OPERATOR_XOR:
        return enif_make_atom(env, "xor");
    case CAIRO_OPERATOR_ADD:
        return enif_make_atom(env, "add");
    case CAIRO_OPERATOR_SATURATE:
        return enif_make_atom(env, "saturate");
    case CAIRO_OPERATOR_MULTIPLY:
        return enif_make_atom(env, "multiply");
    case CAIRO_OPERATOR_SCREEN:
        return enif_make_atom(env, "screen");
    case CAIRO_OPERATOR_OVERLAY:
        return enif_make_atom(env, "overlay");
    case CAIRO_OPERATOR_DARKEN:
        return enif_make_atom(env, "darken");
    case CAIRO_OPERATOR_LIGHTEN:
        return enif_make_atom(env, "lighten");
    case CAIRO_OPERATOR_COLOR_DODGE:
        return enif_make_atom(env, "color_dodge");
    case CAIRO_OPERATOR_COLOR_BURN:
        return enif_make_atom(env, "color_burn");
    case CAIRO_OPERATOR_HARD_LIGHT:
        return enif_make_atom(env, "hard_light");
    case CAIRO_OPERATOR_SOFT_LIGHT:
        return enif_make_atom(env, "soft_light");
    case CAIRO_OPERATOR_DIFFERENCE:
        return enif_make_atom(env, "difference");
    case CAIRO_OPERATOR_EXCLUSION:
        return enif_make_atom(env, "exclusion");
    case CAIRO_OPERATOR_HSL_HUE:
        return enif_make_atom(env, "hsl_hue");
    case CAIRO_OPERATOR_HSL_SATURATION:
        return enif_make_atom(env, "hsl_saturation");
    case CAIRO_OPERATOR_HSL_COLOR:
        return enif_make_atom(env, "hsl_color");
    case CAIRO_OPERATOR_HSL_LUMINOSITY:
        return enif_make_atom(env, "hsl_luminosity");
    default:
        return enif_make_badarg(env);
    }
}

/**
 * Wraps cairo_get_reference_count(cairo_t *cr)
 * @brief EX_get_reference_count
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_get_reference_count(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    unsigned int count = cairo_get_reference_count(context->data);
    return enif_make_int(env, count);
}

/**
 * Wraps cairo_get_source(cairo_t *cr)
 * @brief EX_get_source
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_get_source(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    ERL_MAKE_INSTANCE(cairo_pattern_t_TYPE, cairo_pattern_t_RT, instance);
    ERL_ASSERT(instance);

    instance->data = cairo_get_source(context->data);

    // The object is owned by cairo, so don't garbage collect it
    return enif_make_resource(env, instance);
}

/**
 * Wraps cairo_get_target(cairo_t *cr)
 * @brief EX_get_target
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_get_target(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    ERL_MAKE_INSTANCE(cairo_surface_t_TYPE, cairo_surface_t_RT, instance);
    ERL_ASSERT(instance);

    instance->data = cairo_get_target(context->data);

    // The object is owned by cairo, so don't garbage collect it
    return enif_make_resource(env, instance);
}

/**
 * Wraps cairo_get_tolerance(cairo_t *cr)
 * @brief EX_get_tolerance
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_get_tolerance(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    double tolerance = cairo_get_tolerance(context->data);
    return enif_make_double(env, tolerance);
}

// TODO
// MISSING
// cairo_glyph_*

/**
 * Wraps cairo_has_current_point(cairo_t *cr)
 * @brief EX_has_current_point
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_has_current_point(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    cairo_bool_t result = cairo_has_current_point(context->data);
    return ERL_BOOL(result);
}

/**
 * Wraps cairo_identity_matrix(cairo_t *cr)
 * @brief EX_identity_matrix
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_identity_matrix(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    cairo_identity_matrix(context->data);
    return ERL_OK;
}

/**
 * Wraps cairo_image_surface_create_from_png(const char *filename)
 * @brief EX_image_surface_create_from_png
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_image_surface_create_from_png(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_UTF8_STRING(0, file_name);

    ERL_MAKE_INSTANCE(cairo_surface_t_TYPE, cairo_surface_t_RT, instance);
    ERL_ASSERT(instance);

    instance->data = cairo_image_surface_create_from_png(file_name);

    // Create a garbage-collectable resource
    ERL_MAKE_GC_RES(instance, surface);
    return ERL_MAKE_OK_TUPLE(surface);

}

/**
 * Wraps cairo_image_surface_get_height(cairo_surface_t *surface)
 * @brief EX_image_surface_get_height
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_image_surface_get_height(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_surface_t_TYPE, cairo_surface_t_RT, 0, surface);
    ERL_ASSERT(surface);

    int height = cairo_image_surface_get_height(surface->data);
    return enif_make_int(env, height);
}

/**
 * Wraps cairo_image_surface_get_width(cairo_surface_t *surface)
 * @brief EX_image_surface_get_width
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_image_surface_get_width(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_surface_t_TYPE, cairo_surface_t_RT, 0, surface);
    ERL_ASSERT(surface);

    int width = cairo_image_surface_get_width(surface->data);
    return enif_make_int(env, width);
}

/**
 * Wraps cairo_image_surface_get_stride(cairo_surface_t *surface)
 * @brief EX_image_surface_get_stride
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_image_surface_get_stride(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_surface_t_TYPE, cairo_surface_t_RT, 0, surface);
    ERL_ASSERT(surface);

    int stride = cairo_image_surface_get_stride(surface->data);
    return enif_make_int(env, stride);
}

/**
 * Wraps cairo_in_clip(cairo_t *cr, double x, double y)
 * @brief EX_in_clip
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_in_clip(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(3);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    double x, y;
    enif_get_double(env, argv[1], &x);
    enif_get_double(env, argv[2], &y);

    cairo_bool_t result = cairo_in_clip(context->data, x, y);
    return ERL_BOOL(result);
}

/**
 * Wraps cairo_in_fill(cairo_t *cr, double x, double y)
 * @brief EX_in_fill
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_in_fill(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(3);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    double x, y;
    enif_get_double(env, argv[1], &x);
    enif_get_double(env, argv[2], &y);

    cairo_bool_t result = cairo_in_fill(context->data, x, y);
    return ERL_BOOL(result);
}

/**
 * Wraps cairo_in_stroke(cairo_t *cr, double x, double y)
 * @brief EX_in_stroke
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_in_stroke(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(3);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    double x, y;
    enif_get_double(env, argv[1], &x);
    enif_get_double(env, argv[2], &y);

    cairo_bool_t result = cairo_in_fill(context->data, x, y);
    return ERL_BOOL(result);
}

/**
 * Wraps cairo_mask(cairo_t *cr, cairo_pattern_t *pattern)
 * @brief EX_mask
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_mask(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(2);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    ERL_GET_INSTANCE(cairo_pattern_t_TYPE, cairo_pattern_t_RT, 1, pattern);
    ERL_ASSERT(pattern);

    cairo_mask(context->data, pattern->data);

    return ERL_OK;
}

/**
 * Wraps cairo_mask_surface(cairo_t *cr, cairo_surface_t *surface)
 * @brief EX_mask_surface
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_mask_surface(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(4);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    ERL_GET_INSTANCE(cairo_surface_t_TYPE, cairo_surface_t_RT, 1, surface);
    ERL_ASSERT(surface);

    double surface_x, surface_y;
    enif_get_double(env, argv[2], &surface_x);
    enif_get_double(env, argv[3], &surface_y);

    cairo_mask_surface(context->data, surface->data, surface_x, surface_y);

    return ERL_OK;
}

/**
 * Wraps cairo_matrix_init(cairo_matrix_t *matrix, double xx, double yx, double xy, double x0, doubel y0)
 * @brief EX_matrix_init
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_matrix_init(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(6);

    double xx, yx, xy, yy, x0, y0;
    enif_get_double(env, argv[0], &xx);
    enif_get_double(env, argv[1], &yx);
    enif_get_double(env, argv[2], &xy);
    enif_get_double(env, argv[3], &yy);
    enif_get_double(env, argv[4], &x0);
    enif_get_double(env, argv[5], &y0);

    cairo_matrix_t matrix;
    cairo_matrix_init(&matrix, xx, yx, xy, yy, x0, y0);

    return ERL_EXPORT_MATRIX(matrix);
}

/**
 * Wraps cairo_matrix_init_identity(cairo_matrix_t *matrix)
 * @brief EX_matrix_init_identity
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_matrix_init_identity(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(0);
    cairo_matrix_t matrix;
    cairo_matrix_init_identity(&matrix);
    return ERL_EXPORT_MATRIX(matrix);
}

/**
 * Wraps cairo_matrix_init_rotate(cairo_matrix_t *matrix, double radians)
 * @brief EX_matrix_init_rotate
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_matrix_init_rotate(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);

    double radians;
    enif_get_double(env, argv[0], &radians);

    cairo_matrix_t matrix;
    cairo_matrix_init_rotate(&matrix, radians);

    return ERL_EXPORT_MATRIX(matrix);
}

/**
 * Wraps cairo_matrix_init_scale(cairo_matrix_t *matrix, double sx, double sy)
 * @brief EX_matrix_init_scale
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_matrix_init_scale(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(2);

    double sx, sy;
    enif_get_double(env, argv[0], &sx);
    enif_get_double(env, argv[1], &sy);

    cairo_matrix_t matrix;
    cairo_matrix_init_scale(&matrix, sx, sy);

    return ERL_EXPORT_MATRIX(matrix);
}

/**
 * Wraps cairo_matrix_init_translate(cairo_matrix_t *matrix, double tx, double ty)
 * @brief EX_matrix_init_translate
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_matrix_init_translate(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(2);

    double tx, ty;
    enif_get_double(env, argv[0], &tx);
    enif_get_double(env, argv[1], &ty);

    cairo_matrix_t matrix;
    cairo_matrix_init_translate(&matrix, tx, ty);

    return ERL_EXPORT_MATRIX(matrix);
}

/**
 * Wraps cairo_matrix_invert(cairo_matrix_t *matrix)
 * @brief EX_matrix_invert
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_matrix_invert(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_IMPORT_MATRIX(0, matrix);

    cairo_status_t status = cairo_matrix_invert(&matrix);
    if (status == CAIRO_STATUS_INVALID_MATRIX) {
        return enif_make_badarg(env);
    } else {
        return ERL_EXPORT_MATRIX(matrix);
    }
}

/**
 * Wraps cairo_matrix_multiply(
 *  cairo_matrix_t *matrix,
 *  const cairo_matrix_t *a,
 *  const cairo_matrix_t *b
 * )
 * @brief EX_matrix_multiply
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_matrix_multiply(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(2);
    ERL_IMPORT_MATRIX(0, matrix_a);
    ERL_IMPORT_MATRIX(1, matrix_b);

    cairo_matrix_t result;
    cairo_matrix_multiply(&result, &matrix_a, &matrix_b);
    return ERL_EXPORT_MATRIX(result);
}

/**
 * Wraps cairo_matrix_rotate(
 *  cairo_matrix_t *matrix,
 *  double radians
 * )
 * @brief EX_matrix_rotate
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_matrix_rotate(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(2);
    ERL_IMPORT_MATRIX(0, matrix);

    double radians;
    enif_get_double(env, argv[1], &radians);

    cairo_matrix_rotate(&matrix, radians);
    return ERL_EXPORT_MATRIX(matrix);
}

/**
 * Wraps cairo_matrix_scale(
 *  cairo_matrix_t *matrix,
 *  double sx,
 *  double sy
 * )
 * @brief EX_matrix_scale
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_matrix_scale(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(3);
    ERL_IMPORT_MATRIX(0, matrix);

    double sx, sy;
    enif_get_double(env, argv[1], &sx);
    enif_get_double(env, argv[2], &sy);

    cairo_matrix_scale(&matrix, sx, sy);
    return ERL_EXPORT_MATRIX(matrix);
}

/**
 * Wraps cairo_matrix_transform_distance(
 *  cairo_matrix_t *matrix,
 *  double *dx,
 *  double *dy
 * )
 * @brief EX_matrix_transform_distance
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_matrix_transform_distance(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(3);
    ERL_IMPORT_MATRIX(0, matrix);

    double dx, dy;
    enif_get_double(env, argv[1], &dx);
    enif_get_double(env, argv[2], &dy);

    cairo_matrix_transform_distance(&matrix, &dx, &dy);
    return enif_make_tuple2(env, enif_make_double(env, dx), enif_make_double(env, dy));
}

/**
 * Wraps cairo_matrix_transform_point(
 *  cairo_matrix_t *matrix,
 *  double *x,
 *  double *y
 * )
 * @brief EX_matrix_transform_distance
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_matrix_transform_point(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(3);
    ERL_IMPORT_MATRIX(0, matrix);

    double x, y;
    enif_get_double(env, argv[1], &x);
    enif_get_double(env, argv[2], &y);

    cairo_matrix_transform_point(&matrix, &x, &y);
    return enif_make_tuple2(env, enif_make_double(env, x), enif_make_double(env, y));
}

/**
 * Wraps cairo_matrix_translate(
 *  cairo_matrix_t *matrix,
 *  double tx,
 *  double ty
 * )
 * @brief EX_matrix_translate
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_matrix_translate(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(3);
    ERL_IMPORT_MATRIX(0, matrix);

    double tx, ty;
    enif_get_double(env, argv[1], &tx);
    enif_get_double(env, argv[2], &ty);

    cairo_matrix_translate(&matrix, tx, ty);
    return ERL_EXPORT_MATRIX(matrix);
}

// TODO
// MISSING
// cairo_mesh_pattern_*


/**
 * Wraps cairo_new_path()
 * @brief EX_new_path
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_new_path(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    cairo_new_path(context->data);

    return ERL_OK;
}

/**
 * Wraps cairo_new_sub_path()
 * @brief EX_new_sub_path
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_new_sub_path(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    cairo_new_sub_path(context->data);

    return ERL_OK;
}

/**
 * Wraps cairo_paint()
 * @brief EX_paint
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_paint(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    cairo_paint(context->data);

    return ERL_OK;
}

/**
 * Wraps cairo_paint_with_alpha()
 * @brief EX_paint_with_alpha
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_paint_with_alpha(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(2);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    double alpha;
    enif_get_double(env, argv[1], &alpha);

    cairo_paint_with_alpha(context->data, alpha);

    return ERL_OK;
}

/**
 * Wraps cairo_path_extents(cairo_t* cr, double *x1, double *y1, double *x2, double *y2)
 * @brief EX_path_extents
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_path_extents(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    double x1, y1, x2, y2;
    cairo_path_extents(context->data, &x1, &y1, &x2, &y2);

    return enif_make_tuple4(env,
                            enif_make_double(env, x1),
                            enif_make_double(env, y1),
                            enif_make_double(env, y1),
                            enif_make_double(env, y2));
}

/**
 * Wraps cairo_pattern_add_color_stop_rgb(cairo_pattern_t* pattern,
 *  double offset,
 *  double red,
 *  double green,
 *  double blue);
 * @brief EX_pattern_add_color_stop_rgb
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_pattern_add_color_stop_rgb(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(5);
    ERL_GET_INSTANCE(cairo_pattern_t_TYPE, cairo_pattern_t_RT, 0, pattern);
    ERL_ASSERT(pattern);

    double offset, red, green, blue;
    enif_get_double(env, argv[1], &offset);
    enif_get_double(env, argv[2], &red);
    enif_get_double(env, argv[3], &green);
    enif_get_double(env, argv[4], &blue);

    cairo_pattern_add_color_stop_rgb(pattern->data, offset, red, green, blue);

    return ERL_OK;
}

/**
 * Wraps cairo_pattern_add_color_stop_rgba(cairo_pattern_t* pattern,
 *  double offset,
 *  double red,
 *  double green,
 *  double blue,
 *  double alpha);
 * @brief EX_pattern_add_color_stop_rgba
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_pattern_add_color_stop_rgba(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(6);
    ERL_GET_INSTANCE(cairo_pattern_t_TYPE, cairo_pattern_t_RT, 0, pattern);
    ERL_ASSERT(pattern);

    double offset, red, green, blue, alpha;
    enif_get_double(env, argv[1], &offset);
    enif_get_double(env, argv[2], &red);
    enif_get_double(env, argv[3], &green);
    enif_get_double(env, argv[4], &blue);
    enif_get_double(env, argv[5], &alpha);

    cairo_pattern_add_color_stop_rgba(pattern->data, offset, red, green, blue, alpha);

    return ERL_OK;
}

/**
 * Wraps cairo_pattern_create_for_surface(cairo_surface_t* surface);
 * @brief EX_pattern_add_color_stop_rgba
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_pattern_create_for_surface(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_surface_t_TYPE, cairo_surface_t_RT, 0, surface)
    ERL_ASSERT(surface);

    ERL_MAKE_INSTANCE(cairo_pattern_t_TYPE, cairo_pattern_t_RT, instance);
    ERL_ASSERT(instance);

    instance->data = cairo_pattern_create_for_surface(surface->data);

    // Create a garbage-collectable resource
    ERL_MAKE_GC_RES(instance, surface_term);
    return ERL_MAKE_OK_TUPLE(surface_term);
}

/**
 * Wraps cairo_pattern_create_linear(double x0, double y0, double x1, double y1);
 * @brief EX_pattern_create_linear
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_pattern_create_linear(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(4);

    double x0, y0, x1, y1;
    enif_get_double(env, argv[0], &x0);
    enif_get_double(env, argv[1], &y0);
    enif_get_double(env, argv[2], &x1);
    enif_get_double(env, argv[3], &y1);

    ERL_MAKE_INSTANCE(cairo_pattern_t_TYPE, cairo_pattern_t_RT, instance);
    ERL_ASSERT(instance);

    instance->data = cairo_pattern_create_linear(x0, y0, x1, y1);

    // Create a garbage-collectable resource
    ERL_MAKE_GC_RES(instance, pattern_term);
    return ERL_MAKE_OK_TUPLE(pattern_term);
}

// TODO
// MISSING
// cairo_pattern_create_mesh

/**
 * Wraps cairo_pattern_create_radial(
 *  double cx0,
 *  double cy0,
 *  double radius0,
 *  double cx1,
 *  double xy1,
 *  double radius1);
 * @brief EX_pattern_create_radial
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_pattern_create_radial(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(6);

    double cx0, cy0, radius0, cx1, cy1, radius1;
    enif_get_double(env, argv[0], &cx0);
    enif_get_double(env, argv[1], &cy0);
    enif_get_double(env, argv[2], &radius0);
    enif_get_double(env, argv[3], &cx1);
    enif_get_double(env, argv[4], &cy1);
    enif_get_double(env, argv[5], &radius1);


    ERL_MAKE_INSTANCE(cairo_pattern_t_TYPE, cairo_pattern_t_RT, instance);
    ERL_ASSERT(instance);

    instance->data = cairo_pattern_create_radial(cx0, cy0, radius0, cx1, cy1, radius1);

    // Create a garbage-collectable resource
    ERL_MAKE_GC_RES(instance, pattern_term);
    return ERL_MAKE_OK_TUPLE(pattern_term);
}

// TODO
// MISSING
// cairo_pattern_create_raster_source

/**
 * Wraps cairo_pattern_create_rgb(double red, double green, double blue);
 * @brief EX_pattern_create_rgb
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_pattern_create_rgb(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(3);

    double red, green, blue;
    enif_get_double(env, argv[0], &red);
    enif_get_double(env, argv[1], &green);
    enif_get_double(env, argv[2], &blue);


    ERL_MAKE_INSTANCE(cairo_pattern_t_TYPE, cairo_pattern_t_RT, instance);
    ERL_ASSERT(instance);

    instance->data = cairo_pattern_create_rgb(red, green, blue);

    // Create a garbage-collectable resource
    ERL_MAKE_GC_RES(instance, pattern_term);
    return ERL_MAKE_OK_TUPLE(pattern_term);
}

/**
 * Wraps cairo_pattern_create_rgba(double red, double green, double blue, double alpha);
 * @brief EX_pattern_create_rgba
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_pattern_create_rgba(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(4);

    double red, green, blue, alpha;
    enif_get_double(env, argv[0], &red);
    enif_get_double(env, argv[1], &green);
    enif_get_double(env, argv[2], &blue);
    enif_get_double(env, argv[2], &alpha);

    ERL_MAKE_INSTANCE(cairo_pattern_t_TYPE, cairo_pattern_t_RT, instance);
    ERL_ASSERT(instance);

    instance->data = cairo_pattern_create_rgba(red, green, blue, alpha);

    // Create a garbage-collectable resource
    ERL_MAKE_GC_RES(instance, pattern_term);
    return ERL_MAKE_OK_TUPLE(pattern_term);
}

/**
 * Wraps cairo_pattern_get_color_stop_count(cairo_patter_t *pattern, int *count);
 * @brief EX_pattern_get_color_stop_count
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_pattern_get_color_stop_count(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_pattern_t_TYPE, cairo_pattern_t_RT, 0, pattern)
    ERL_ASSERT(pattern);

    int count;
    cairo_status_t status = cairo_pattern_get_color_stop_count(pattern->data, &count);
    if (status == CAIRO_STATUS_SUCCESS) {
        return enif_make_int(env, count);
    } else {
        return enif_make_badarg(env);
    }
}

/**
 * Wraps cairo_pattern_get_rgba(cairo_patter_t *pattern, double *red, double *green, double *blue, double *aplha);
 * @brief EX_pattern_get_rgba
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_pattern_get_rgba(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_pattern_t_TYPE, cairo_pattern_t_RT, 0, pattern)
    ERL_ASSERT(pattern);

    double red, green, blue, alpha;

    cairo_status_t status = cairo_pattern_get_rgba(pattern->data, &red, &green, &blue, &alpha);
    if (status == CAIRO_STATUS_SUCCESS) {
        return enif_make_tuple4(env,
                    enif_make_double(env, red),
                    enif_make_double(env, green),
                    enif_make_double(env, blue),
                    enif_make_double(env, alpha));
    } else {
        return enif_make_badarg(env);
    }
}

/**
 * Wraps cairo_pattern_get_surface(cairo_patter_t *pattern, cairo_surface:t **surface);
 * @brief EX_pattern_get_surface
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_pattern_get_surface(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_pattern_t_TYPE, cairo_pattern_t_RT, 0, pattern)
    ERL_ASSERT(pattern);

    cairo_surface_t *surface;

    cairo_status_t status = cairo_pattern_get_surface(pattern->data, &surface);
    if (status == CAIRO_STATUS_SUCCESS) {
        ERL_MAKE_INSTANCE(cairo_surface_t_TYPE, cairo_surface_t_RT, instance);
        ERL_ASSERT(instance);

        instance->data = surface;
        // The surface is owned by the pattern so don't garbage collect it
        return enif_make_resource(env, instance);
    } else {
        return enif_make_badarg(env);
    }
}

/**
 * Wraps cairo_pattern_get_type(cairo_patter_t *pattern);
 * @brief EX_pattern_get_type
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_pattern_get_type(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_pattern_t_TYPE, cairo_pattern_t_RT, 0, pattern)
    ERL_ASSERT(pattern);

    cairo_pattern_type_t type = cairo_pattern_get_type(pattern->data);
    switch (type) {
    case CAIRO_PATTERN_TYPE_SOLID:
        return enif_make_atom(env, "solid");
    case CAIRO_PATTERN_TYPE_SURFACE:
        return enif_make_atom(env, "surface");
    case CAIRO_PATTERN_TYPE_LINEAR:
        return enif_make_atom(env, "linear");
    case CAIRO_PATTERN_TYPE_RADIAL:
        return enif_make_atom(env, "radial");
    case CAIRO_PATTERN_TYPE_MESH:
        return enif_make_atom(env, "mesh");
    case CAIRO_PATTERN_TYPE_RASTER_SOURCE:
        return enif_make_atom(env, "raster_source");
    default:
        return enif_make_badarg(env);
    }
}

// TODO (?)
// MISSING
// cairo_pattern_get_user_data
// cairo_pattern_reference
/**
  * cairo_pattern_reference is not wrapped, because it would allow
  * a user to increase the reference count of the object and thus
  * circumvent garbage collection. If that function was accessible
  * it's counterpart `cairo_pattern_destroy` must also be.
  * I decided against this but there might be a good reason to make
  * them accessible at some later point
  */

/**
 * Wraps cairo_pattern_set_extend(cairo_patter_t *pattern, cairo_extend_t extend);
 * @brief EX_pattern_set_extend
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_pattern_set_extend(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(2);
    ERL_GET_INSTANCE(cairo_pattern_t_TYPE, cairo_pattern_t_RT, 0, pattern)
    ERL_ASSERT(pattern);

    cairo_extend_t extend;
    ERL_TRY_ATOM(1,     ET_none,    extend, CAIRO_EXTEND_NONE)
    _ERL_TRY_ATOM(1,    ET_repeat,  extend, CAIRO_EXTEND_REPEAT)
    _ERL_TRY_ATOM(1,    ET_reflect, extend, CAIRO_EXTEND_REFLECT)
    _ERL_TRY_ATOM(1,    ET_pad,     extend, CAIRO_EXTEND_PAD)
    _ERL_FAIL_ATOM;

    cairo_pattern_set_extend(pattern->data, extend);

    return ERL_OK;
}

/**
 * Wraps cairo_pattern_set_filter(cairo_patter_t *pattern, cairo_filter_t extend);
 * @brief EX_pattern_set_filter
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_pattern_set_filter(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(2);
    ERL_GET_INSTANCE(cairo_pattern_t_TYPE, cairo_pattern_t_RT, 0, pattern)
    ERL_ASSERT(pattern);

    cairo_extend_t filter;
    ERL_TRY_ATOM(1,     ET_fast,        filter, CAIRO_FILTER_FAST)
    _ERL_TRY_ATOM(1,    ET_good,        filter, CAIRO_FILTER_GOOD)
    _ERL_TRY_ATOM(1,    ET_best,        filter, CAIRO_FILTER_BEST)
    _ERL_TRY_ATOM(1,    ET_nearest,     filter, CAIRO_FILTER_NEAREST)
    _ERL_TRY_ATOM(1,    ET_bilinear,    filter, CAIRO_FILTER_BILINEAR)
    _ERL_TRY_ATOM(1,    ET_gaussian,    filter, CAIRO_FILTER_GAUSSIAN)
    _ERL_FAIL_ATOM;

    cairo_pattern_set_filter(pattern->data, filter);

    return ERL_OK;
}

/**
 * Wraps cairo_pattern_set_matrix(cairo_patter_t *pattern, const cairo_matrix_t *matrix);
 * @brief EX_pattern_set_matrix
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_pattern_set_matrix(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(2);
    ERL_GET_INSTANCE(cairo_pattern_t_TYPE, cairo_pattern_t_RT, 0, pattern)
    ERL_ASSERT(pattern);

    ERL_IMPORT_MATRIX(1, matrix);

    cairo_pattern_set_matrix(pattern->data, &matrix);

    return ERL_OK;
}

/**
 * Wraps cairo_pattern_status(cairo_patter_t *pattern);
 * @brief EX_pattern_set_matrix
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_pattern_status(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_pattern_t_TYPE, cairo_pattern_t_RT, 0, pattern)
    ERL_ASSERT(pattern);

    cairo_status_t status = cairo_pattern_status(pattern->data);
    switch (status) {
    case CAIRO_STATUS_SUCCESS:
        return enif_make_atom(env, "success");
    case CAIRO_STATUS_NO_MEMORY:
        return enif_make_atom(env, "no_memory");
    case CAIRO_STATUS_INVALID_MATRIX:
        return enif_make_atom(env, "invalid_matrix");
    case CAIRO_STATUS_PATTERN_TYPE_MISMATCH:
        return enif_make_atom(env, "pattern_type_mismatch");
    case CAIRO_STATUS_INVALID_MESH_CONSTRUCTION:
        return enif_make_atom(env, "invalid_mesh_construction");
    default:
        return enif_make_badarg(env);
    }
}

// TODO
// MISSING
// cairo_pdf_*
// cairo_ps_*

/**
 * Wraps cairo_push_group(cairo_t *cr);
 * @brief EX_push_group
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_push_group(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context)
    ERL_ASSERT(context);

    cairo_push_group(context->data);

    return ERL_OK;
}

// TODO
// MISSING
// cairo_pdf_*
// cairo_ps_*

/**
 * Wraps cairo_pop_group(cairo_t *cr);
 * @brief EX_pop_group
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_pop_group(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context)
    ERL_ASSERT(context);

    cairo_pop_group(context->data);

    return ERL_OK;
}

/**
 * Wraps cairo_pop_group_to_source(cairo_t *cr);
 * @brief EX_pop_group_to_source
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_pop_group_to_source(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context)
    ERL_ASSERT(context);

    cairo_pop_group_to_source(context->data);

    return ERL_OK;
}


/**
 * Wraps cairo_push_group_with_content(cairo_t *cr, cairo_content_t content);
 * @brief EX_push_group_with_content
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_push_group_with_content(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(2);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context)
    ERL_ASSERT(context);

    cairo_content_t content;
    ERL_TRY_ATOM(1,     ET_color,       content, CAIRO_CONTENT_COLOR)
    _ERL_TRY_ATOM(1,    ET_alpha,       content, CAIRO_CONTENT_ALPHA)
    _ERL_TRY_ATOM(1,    ET_color_alpha, content, CAIRO_CONTENT_COLOR_ALPHA)
    _ERL_FAIL_ATOM;

    cairo_push_group_with_content(context->data, content);

    return ERL_OK;
}

/**
 * Wraps cairo_recording_surface_create(
 *  cairo_content_t content,
 *  const cairo_rectangle_t *extents);
 * @brief EX_recording_surface_create
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_recording_surface_create(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(2);

    cairo_content_t content;
    ERL_TRY_ATOM(0,     ET_color,       content, CAIRO_CONTENT_COLOR)
    _ERL_TRY_ATOM(0,    ET_alpha,       content, CAIRO_CONTENT_ALPHA)
    _ERL_TRY_ATOM(0,    ET_color_alpha, content, CAIRO_CONTENT_COLOR_ALPHA)
    _ERL_FAIL_ATOM;

    int arity = 4;
    const ERL_NIF_TERM *tuple;
    ERL_ASSERT(enif_get_tuple(env, argv[1], &arity, &tuple));

    cairo_rectangle_t rect;
    enif_get_double(env, tuple[0], &rect.x);
    enif_get_double(env, tuple[1], &rect.y);
    enif_get_double(env, tuple[2], &rect.width);
    enif_get_double(env, tuple[3], &rect.height);

    ERL_MAKE_INSTANCE(cairo_surface_t_TYPE, cairo_surface_t_RT, instance);
    ERL_ASSERT(instance);

    instance->data = cairo_recording_surface_create(content, &rect);

    // Create a garbage-collectable resource
    ERL_MAKE_GC_RES(instance, surface);
    return ERL_MAKE_OK_TUPLE(surface);
}

/**
 * Wraps cairo_recording_surface_get_extents(
 *   cairo_surface_t *surface,
 *   cairo_rectangle_t *extents);
 * @brief EX_recording_surface_get_extents
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_recording_surface_get_extents(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_surface_t_TYPE, cairo_surface_t_RT, 0, surface)
    ERL_ASSERT(surface);

    cairo_rectangle_t extents;
    if (cairo_recording_surface_get_extents(surface->data, &extents)) {
        return enif_make_tuple4(env,
                                enif_make_double(env, extents.x),
                                enif_make_double(env, extents.y),
                                enif_make_double(env, extents.width),
                                enif_make_double(env, extents.height));
    } else {
        return enif_make_badarg(env);
    }
}

/**
 * Wraps cairo_recording_surface_ink_extents(
 *      cairo_surface_t *surface,
 *      double *x0,
 *      double *y0,
 *      double *width,
 *      double *height);
 * @brief EX_recording_surface_ink_extents
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_recording_surface_ink_extents(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_surface_t_TYPE, cairo_surface_t_RT, 0, surface)
    ERL_ASSERT(surface);

    double x,y,w,h;
    cairo_recording_surface_ink_extents(surface->data, &x,&y,&w,&h);
    return enif_make_tuple4(env,
                            enif_make_double(env, x),
                            enif_make_double(env, y),
                            enif_make_double(env, w),
                            enif_make_double(env, h));
}

/**
 * Wraps cairo_rectangle(
 *      cairo_t *cr,
 *      double x,
 *      double y,
 *      double width,
 *      double height);
 * @brief EX_rectangle
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_rectangle(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(5);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    double x,y,w,h;
    enif_get_double(env, argv[1], &x);
    enif_get_double(env, argv[2], &y);
    enif_get_double(env, argv[3], &w);
    enif_get_double(env, argv[4], &h);

    cairo_rectangle(context->data, x, y, w, h);

    return ERL_OK;
}

/**
 * Wraps cairo_region_contains_point(const cairo_region_t *region,
                                                         int x,
                                                         int y);
 * @brief EX_region_contains_point
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_region_contains_point(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(3);
    ERL_GET_INSTANCE(cairo_region_t_TYPE, cairo_region_t_RT, 0, region);
    ERL_ASSERT(region);

    ERL_GET_INT(1, x);
    ERL_GET_INT(2, y);

    cairo_bool_t result = cairo_region_contains_point(region->data, x, y);
    return ERL_BOOL(result);
}

/**
 * Wraps cairo_region_contains_rectangle(
 *  const cairo_region_t *region,
 *  const cairo_rectangle_int_t *rectangle);
 * @brief EX_region_contains_point
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_region_contains_rectangle(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(2);
    ERL_GET_INSTANCE(cairo_region_t_TYPE, cairo_region_t_RT, 0, region);
    ERL_ASSERT(region);

    int arity = 4;
    const ERL_NIF_TERM *tuple;
    ERL_ASSERT(enif_get_tuple(env, argv[1], &arity, &tuple));

    cairo_rectangle_int_t rect;

    enif_get_int(env, tuple[0], &rect.x);
    enif_get_int(env, tuple[1], &rect.y);
    enif_get_int(env, tuple[2], &rect.width);
    enif_get_int(env, tuple[3], &rect.height);

    cairo_region_overlap_t result = cairo_region_contains_rectangle(region->data, &rect);
    switch (result) {
    case CAIRO_REGION_OVERLAP_IN:
        return enif_make_atom(env, "in");
    case CAIRO_REGION_OVERLAP_OUT:
        return enif_make_atom(env, "out");
    case CAIRO_REGION_OVERLAP_PART:
        return enif_make_atom(env, "part");
    }
}


/**
 * Wraps cairo_image_surface_create(cairo_format_t format, int width, int height)
 * @brief EX_image_surface_create
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_image_surface_create(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(3);

    cairo_format_t format = -1;
    ERL_TRY_ATOM(0, ET_invalid,      format, -1)
    _ERL_TRY_ATOM(0, ET_argb32,      format, 0)
    _ERL_TRY_ATOM(0, ET_rgb24,       format, 1)
    _ERL_TRY_ATOM(0, ET_a8,          format, 2)
    _ERL_TRY_ATOM(0, ET_a1,          format, 3)
    _ERL_TRY_ATOM(0, ET_rgb16_565,   format, 4)
    _ERL_TRY_ATOM(0, ET_rgb30,       format, 5)
    _ERL_FAIL_ATOM;

    ERL_GET_INT(1, width);
    ERL_GET_INT(2, height);

    ERL_MAKE_INSTANCE(cairo_surface_t_TYPE, cairo_surface_t_RT, instance);
    ERL_ASSERT(instance);

    instance->data = cairo_image_surface_create(format, width, height);

    // Create a garbage-collectable resource
    ERL_MAKE_GC_RES(instance, surface);
    return ERL_MAKE_OK_TUPLE(surface);
}

/**
 * Wraps cairo_create(cairo_surface_t* target)
 * @brief EX_cairo_create
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_cairo_create (ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_surface_t_TYPE, cairo_surface_t_RT, 0, surface)
    ERL_ASSERT(surface);

    ERL_MAKE_INSTANCE(cairo_t_TYPE, cairo_t_RT, instance);
    ERL_ASSERT(instance);

    instance->data = cairo_create(surface->data);

    // Create a garbage-collectable resource
    ERL_MAKE_GC_RES(instance, context);
    return ERL_MAKE_OK_TUPLE(context);
}

/**
 * Wraps cairo_surface_write_to_png(cairo_surface_t* surface, const char* filename)
 * -> The file name argument is expected to be a UTF-8 encoded binary
 * @brief EX_surface_write_to_png
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_surface_write_to_png (ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(2);
    ERL_GET_INSTANCE(cairo_surface_t_TYPE, cairo_surface_t_RT, 0, surface);
    ERL_ASSERT(surface);

    // Get the filename from the arguments
    ERL_GET_UTF8_STRING(1, file_name);

    cairo_status_t result = cairo_surface_write_to_png(surface->data, file_name);
    return ERL_MAKE_OK_TUPLE(enif_make_int(env, result));
}

/**
 * Wraps cairo_select_font_face(cairo_t *cr,
 *   const char *family,
 *   cairo_font_slant_t slant,
 *   cairo_font_weight_t weight)
 * -> The font family is expected to be a UTF-8 encoded binary
 * @brief EX_select_font_face
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_select_font_face(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(4);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    ERL_GET_UTF8_STRING(1, family);

    cairo_font_slant_t slant = CAIRO_FONT_SLANT_NORMAL;
    cairo_font_weight_t weight = CAIRO_FONT_WEIGHT_NORMAL;

    ERL_TRY_ATOM(2, ET_normal,      slant, 0)
    _ERL_TRY_ATOM(2, ET_italic,     slant, 1)
    _ERL_TRY_ATOM(2, ET_oblique,    slant, 2)
    _ERL_FAIL_ATOM;

    ERL_TRY_ATOM(3, ET_normal,      weight, 0)
    _ERL_TRY_ATOM(3, ET_bold,       weight, 1)
    _ERL_FAIL_ATOM;

    cairo_select_font_face(context->data, family, slant, weight);
    return ERL_OK;
}

/**
 * Wraps cairo_set_font_size(cairo_t *cr, double size);
 * @brief EX_select_font_face
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_set_font_size(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(2);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    double font_size;
    enif_get_double(env, argv[1], &font_size);

    cairo_set_font_size(context->data, font_size);
    return ERL_OK;
}

/**
 * Wraps cairo_set_source_rgb(cairo_t *cr, double red, double green, double blue);
 * @brief EX_set_source_rgb
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_set_source_rgb(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(4);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    double red, green, blue;
    enif_get_double(env, argv[1], &red);
    enif_get_double(env, argv[2], &green);
    enif_get_double(env, argv[3], &blue);

    cairo_set_source_rgb(context->data, red, green, blue);
    return ERL_OK;
}

/**
 * Wraps cairo_move_to(cairo_t *cr, double x, double y)
 * @brief EX_move_to
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_move_to(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(3);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    double x, y;
    enif_get_double(env, argv[1], &x);
    enif_get_double(env, argv[2], &y);

    cairo_move_to(context->data, x, y);
    return ERL_OK;
}

/**
 * Wraps cairo_show_text(cairo_t *cr, const char *utf8)
 * -> The text to be shown is expected to be a UTF-8 encoded binary
 * @brief EX_show_text
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_show_text(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(2);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    ERL_GET_UTF8_STRING(1, text);

    // text now contains UTF-8 Data + terminator char
    cairo_show_text(context->data, text);

    return ERL_OK;
}

/**
 * Wraps cairo_line_to(cairo__t *cr, double x, double y)
 * @brief EX_line_to
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_line_to (ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(3);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);

    double x, y;
    enif_get_double(env, argv[1], &x);
    enif_get_double(env, argv[2], &y);

    cairo_line_to(context->data, x, y);
    return ERL_OK;
}

/**
 * Wraps cairo_stroke(cairo_t *cr)
 * @brief EX_stroke
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_stroke (ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(1);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);
    ERL_ASSERT(context);
    cairo_stroke(context->data);
    return ERL_OK;
}

// ///////////////
// Erlang init
// ///////////////

static ErlNifFunc nif_funcs[] = {
    { "arc",                        6, EX_arc },
    { "arc_negative",               6, EX_arc_negative },
    { "clip",                       1, EX_clip },
    { "clip_extents",               5, EX_clip_extents },
    { "clip_preserve",              1, EX_clip_preserve },
    { "close_path",                 1, EX_close_path },
    { "copy_clip_rectangle_list",   1, EX_copy_clip_rectangle_list },

    { "copy_page",                  1, EX_copy_page },
    { "copy_path",                  1, EX_copy_path },
    { "copy_path_flat",             1, EX_copy_path_flat },
    { "curve_to",                   7, EX_curve_to },
    { "fill",                       1, EX_fill },
    { "fill_extents",               1, EX_fill_extents },
    { "fill_preserve",              1, EX_fill_preserve },
    { "font_extents",               1, EX_font_extents },
    { "get_antialias",              1, EX_get_antialias },
    { "get_current_point",          1, EX_get_current_point },
    { "get_dash",                   1, EX_get_dash },
    { "get_dash_count",             1, EX_get_dash_count },
    { "get_fill_rule",              1, EX_get_fill_rule },

    { "image_surface_create",       3, EX_image_surface_create },
    { "create",                     1, EX_cairo_create },
    { "surface_write_to_png",       2, EX_surface_write_to_png },
    { "select_font_face",           4, EX_select_font_face },
    { "set_font_size",              2, EX_set_font_size },
    { "set_source_rgb",             4, EX_set_source_rgb },
    { "move_to",                    3, EX_move_to },
    { "line_to",                    3, EX_line_to },
    { "show_text",                  2, EX_show_text },
    { "stroke",                     1, EX_stroke }
};

ERL_NIF_INIT(
    Elixir.ExCairo,
    nif_funcs,
    load,
    NULL,
    NULL,
    NULL
)
