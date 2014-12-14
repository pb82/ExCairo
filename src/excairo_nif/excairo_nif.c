#include "./include/excairo_nif.h"

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
    ERL_ASSERT_LOAD(cairo_t_RT);

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
 * Wraps cairo_image_surface_create(cairo_format_t format, int width, int height)
 * @brief EX_image_surface_create
 * @param env
 * @param argc
 * @param argv
 * @return
 */
static ERL_NIF_TERM EX_image_surface_create(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_ASSERT_ARGC(3);

    ERL_GET_INT(0, format);
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
    ERL_GET_INT(2, slant);
    ERL_GET_INT(3, weight);

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
