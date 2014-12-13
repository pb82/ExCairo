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

    // Define cairo_t_TYPE
    cairo_t_RT = enif_open_resource_type(
             env,
             NULL,
             "cairo_t_TYPE",
             gc_cairo_t,
             ERL_NIF_RT_CREATE, NULL);

    // Assert that all definitions were successful
    ERL_ASSERT_LOAD(cairo_t_RT);
    ERL_ASSERT_LOAD(cairo_surface_t_RT);

    // Return success
    return 0;
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
    { "image_surface_create", 3, EX_image_surface_create },
    { "create", 1, EX_cairo_create },
    { "surface_write_to_png", 2, EX_surface_write_to_png },
    { "select_font_face", 4, EX_select_font_face },
    { "set_font_size", 2, EX_set_font_size },
    { "set_source_rgb", 4, EX_set_source_rgb },
    { "move_to", 3, EX_move_to },
    { "line_to", 3, EX_line_to },
    { "show_text", 2, EX_show_text },
    { "stroke", 1, EX_stroke }
};

ERL_NIF_INIT(
    Elixir.ExCairo,
    nif_funcs,
    load,
    NULL,
    NULL,
    NULL
)
