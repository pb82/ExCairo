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
    char file_name[MAX_FILENAME_LENGTH];

    ERL_GET_INSTANCE(cairo_surface_t_TYPE, cairo_surface_t_RT, 0, surface)

    // Get the filename from the arguments
    enif_get_string(env, argv[1], file_name, MAX_FILENAME_LENGTH, ERL_NIF_LATIN1);

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
    char font_family[MAX_FONTFMLY_LENGTH];

    ERL_GET_INT(2, slant);
    ERL_GET_INT(3, weight);
    ERL_GET_INSTANCE(cairo_t_TYPE, cairo_t_RT, 0, context);

    // Get font family string from arguments
    enif_get_string(env, argv[1], font_family, MAX_FONTFMLY_LENGTH, ERL_NIF_LATIN1);

    cairo_select_font_face(context->data, font_family, (cairo_font_slant_t) slant, (cairo_font_weight_t) weight);
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

    double font_size;
    enif_get_double(env, argv[1], &font_size);

    cairo_set_font_size(context->data, font_size);
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
};

ERL_NIF_INIT(
    Elixir.ExCairo,
    nif_funcs,
    load,
    NULL,
    NULL,
    NULL
)
