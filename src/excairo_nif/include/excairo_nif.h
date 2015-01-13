#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "erl_nif.h"
#include "cairo.h"

#define MAX_TUPLE_LENGTH 32

// Macro definitions
// --------------------------------------------------------------------------------

#define ERL_ASSERT(condition) if (!(condition)) return enif_make_badarg(env)
#define ERL_ASSERT_ARGC(count) if (argc != count) return enif_make_badarg(env)

#define ERL_GET_INT(pos, target) int target; if(!enif_get_int(env, argv[pos], &target)) return enif_make_badarg(env);

// Create a new instance given an erlang resource type
#define ERL_MAKE_INSTANCE(type, rt, name) \
    type *instance; \
    name = enif_alloc_resource(rt, sizeof(type));

// Get a pointer to a resource type from an argument
#define ERL_GET_INSTANCE(type, rt, pos, name) \
    type* name = NULL; \
    enif_get_resource(env, argv[pos], rt, (void**) &name);

// Create a garbage collectable resource instance
#define ERL_MAKE_GC_RES(object, name) \
    ERL_NIF_TERM name = enif_make_resource(env, object); \
    enif_release_resource(object);

#define ERL_GET_UTF8_STRING(pos, name) \
    ErlNifBinary bin; \
    enif_inspect_binary(env, argv[pos], &bin); \
    char name[bin.size + 1]; \
    memset(name, 0, bin.size + 1); \
    memcpy(name, bin.data, bin.size);

#define ERL_TRY_ATOM(pos, atom, name, value) \
    if (enif_compare(argv[pos], atom) == 0) { name = value; }

#define _ERL_TRY_ATOM(pos, atom, name, value) \
    else if (enif_compare(argv[pos], atom) == 0) { name = value; }

#define _ERL_FAIL_ATOM else { return enif_make_badarg(env); }

// Standard return type
#define ERL_MAKE_OK_TUPLE(data) enif_make_tuple2(env, enif_make_atom(env, "ok"), data)
#define ERL_OK enif_make_atom(env, "ok");

#define ERL_BOOL(cairo_bool) \
    cairo_bool ? enif_make_atom(env, "true") : enif_make_atom(env, "false")

// Use only in nif initializer function
#define ERL_ASSERT_LOAD(condition) if (!(condition)) return -1

// Export a standard matrix with the format
//  --------
// | xx | yx |
// | -- | -- |
// | xy | yy |
// | -- | -- |
// | x0 | y0 |
//  --------
#define ERL_EXPORT_MATRIX(name) enif_make_tuple3(env, \
    enif_make_tuple2(env, enif_make_double(env, name.xx), enif_make_double(env, name.yx)), \
    enif_make_tuple2(env, enif_make_double(env, name.xy), enif_make_double(env, name.yy)), \
    enif_make_tuple2(env, enif_make_double(env, name.x0), enif_make_double(env, name.y0)));

#define ERL_IMPORT_MATRIX(pos, name) \
    int name ## _arity = 3; \
    const ERL_NIF_TERM *name ## _tuple; \
    ERL_ASSERT(enif_get_tuple(env, argv[pos], &name ## _arity, &name ## _tuple)); \
    name ## _arity = 2; \
    const ERL_NIF_TERM *name ## _row_1; \
    const ERL_NIF_TERM *name ## _row_2; \
    const ERL_NIF_TERM *name ## _row_3; \
    ERL_ASSERT(enif_get_tuple(env, name ## _tuple[0], &name ## _arity, &name ## _row_1)); \
    ERL_ASSERT(enif_get_tuple(env, name ## _tuple[0], &name ## _arity, &name ## _row_2)); \
    ERL_ASSERT(enif_get_tuple(env, name ## _tuple[0], &name ## _arity, &name ## _row_3)); \
    cairo_matrix_t name; \
    enif_get_double(env, name ## _row_1[0], &name.xx); \
    enif_get_double(env, name ## _row_1[1], &name.yx); \
    enif_get_double(env, name ## _row_2[0], &name.xy); \
    enif_get_double(env, name ## _row_2[1], &name.yy); \
    enif_get_double(env, name ## _row_3[0], &name.x0); \
    enif_get_double(env, name ## _row_3[1], &name.y0);



// --------------------------------------------------------------------------------

// Predefined erlang terms
// --------------------------------------------------------------------------------

// Surface format related
static ERL_NIF_TERM ET_invalid = NULL;
static ERL_NIF_TERM ET_argb32;
static ERL_NIF_TERM ET_rgb24;
static ERL_NIF_TERM ET_a8;
static ERL_NIF_TERM ET_a1;
static ERL_NIF_TERM ET_rgb16_565;
static ERL_NIF_TERM ET_rgb30;

// Font related
static ERL_NIF_TERM ET_normal;
static ERL_NIF_TERM ET_oblique;
static ERL_NIF_TERM ET_italic;
static ERL_NIF_TERM ET_bold;

// Line caps
static ERL_NIF_TERM ET_butt;
static ERL_NIF_TERM ET_round;
static ERL_NIF_TERM ET_square;

// Line joins
static ERL_NIF_TERM ET_miter;
static ERL_NIF_TERM ET_bevel;

// Operators
static ERL_NIF_TERM ET_clear;
static ERL_NIF_TERM ET_source;
static ERL_NIF_TERM ET_over;
static ERL_NIF_TERM ET_in;
static ERL_NIF_TERM ET_out;
static ERL_NIF_TERM ET_atop;
static ERL_NIF_TERM ET_dest;
static ERL_NIF_TERM ET_dest_over;
static ERL_NIF_TERM ET_dest_in;
static ERL_NIF_TERM ET_dest_out;
static ERL_NIF_TERM ET_dest_atop;
static ERL_NIF_TERM ET_xor;
static ERL_NIF_TERM ET_add;
static ERL_NIF_TERM ET_saturate;
static ERL_NIF_TERM ET_multiply;
static ERL_NIF_TERM ET_screen;
static ERL_NIF_TERM ET_overlay;
static ERL_NIF_TERM ET_darken;
static ERL_NIF_TERM ET_lighten;
static ERL_NIF_TERM ET_color_dodge;
static ERL_NIF_TERM ET_color_burn;
static ERL_NIF_TERM ET_hard_light;
static ERL_NIF_TERM ET_soft_light;
static ERL_NIF_TERM ET_difference;
static ERL_NIF_TERM ET_exclusion;
static ERL_NIF_TERM ET_hsl_hue;
static ERL_NIF_TERM ET_hsl_saturation;
static ERL_NIF_TERM ET_hsl_color;
static ERL_NIF_TERM ET_hsl_luminosity;

// Extend
static ERL_NIF_TERM ET_none;
static ERL_NIF_TERM ET_repeat;
static ERL_NIF_TERM ET_reflect;
static ERL_NIF_TERM ET_pad;

// Filter
static ERL_NIF_TERM ET_fast;
static ERL_NIF_TERM ET_good;
static ERL_NIF_TERM ET_best;
static ERL_NIF_TERM ET_nearest;
static ERL_NIF_TERM ET_bilinear;
static ERL_NIF_TERM ET_gaussian;

// Content
static ERL_NIF_TERM ET_color;
static ERL_NIF_TERM ET_alpha;
static ERL_NIF_TERM ET_color_alpha;

// --------------------------------------------------------------------------------


// cairo_t
// --------------------------------------------------------------------------------

/**
 * Erlang Resource Type representing a
 * cairo_t
 * @brief cairo_t_RT
 */
static ErlNifResourceType *cairo_t_RT = NULL;

/**
 * Struct to use in place of cairo_surface_t when
 * allocating resources with enif_alloc_resource
 */
typedef struct {
    cairo_t *data;
} cairo_t_TYPE;

/**
 * Destructor function to enable garbage collection of
 * cairo_surface_t instances
 * @brief gc_cairo_surface_t
 * @param env Erlang environment
 * @param instance wraps a cairo_surface_t instance
 */
static void gc_cairo_t (ErlNifEnv *env, void *instance) {
    cairo_t_TYPE* context = (cairo_t_TYPE *) instance;
    if (env && context && context->data) {
        cairo_destroy(context->data);
    }
}

// --------------------------------------------------------------------------------


// cairo_surface_t
// --------------------------------------------------------------------------------

/**
 * Erlang Resource Type representing a
 * cairo_surface_t
 * @brief cairo_surface_t_RT
 */
static ErlNifResourceType *cairo_surface_t_RT = NULL;

/**
 * Struct to use in place of cairo_surface_t when
 * allocating resources with enif_alloc_resource
 */
typedef struct {
    cairo_surface_t *data;
} cairo_surface_t_TYPE;

/**
 * Destructor function to enable garbage collection of
 * cairo_surface_t instances
 * @brief gc_cairo_surface_t
 * @param env Erlang environment
 * @param instance wraps a cairo_surface_t instance
 */
static void gc_cairo_surface_t (ErlNifEnv *env, void *instance) {
    cairo_surface_t_TYPE* surface = (cairo_surface_t_TYPE *) instance;
    if (env && surface && surface->data) {
        cairo_surface_destroy(surface->data);
    }
}

// --------------------------------------------------------------------------------


// cairo_path_t
// --------------------------------------------------------------------------------

/**
 * Erlang Resource Type representing a
 * cairo_path_t
 * @brief cairo_surface_t_RT
 */
static ErlNifResourceType *cairo_path_t_RT = NULL;

/**
 * Struct to use in place of cairo_surface_t when
 * allocating resources with enif_alloc_resource
 */
typedef struct {
    cairo_path_t *data;
} cairo_path_t_TYPE;

/**
 * Destructor function to enable garbage collection of
 * cairo_surface_t instances
 * @brief gc_cairo_surface_t
 * @param env Erlang environment
 * @param instance wraps a cairo_surface_t instance
 */
static void gc_cairo_path_t (ErlNifEnv *env, void *instance) {
    cairo_path_t_TYPE* path = (cairo_path_t_TYPE *) instance;
    if (env && path && path->data) {
        cairo_path_destroy(path->data);
    }
}

// --------------------------------------------------------------------------------

// cairo_font_face_t
// --------------------------------------------------------------------------------

/**
 * Erlang Resource Type representing a
 * cairo_path_t
 * @brief cairo_surface_t_RT
 */
static ErlNifResourceType *cairo_font_face_t_RT = NULL;

/**
 * Struct to use in place of cairo_surface_t when
 * allocating resources with enif_alloc_resource
 */
typedef struct {
    cairo_font_face_t *data;
} cairo_font_face_t_TYPE;

/**
 * Destructor function to enable garbage collection of
 * cairo_surface_t instances
 * @brief gc_cairo_surface_t
 * @param env Erlang environment
 * @param instance wraps a cairo_surface_t instance
 */
static void gc_cairo_font_face_t (ErlNifEnv *env, void *instance) {
    cairo_font_face_t_TYPE* ff = (cairo_font_face_t_TYPE *) instance;
    if (env && ff && ff->data) {
        cairo_font_face_destroy(ff->data);
    }
}

// --------------------------------------------------------------------------------

// cairo_font_options_t
// --------------------------------------------------------------------------------

/**
 * Erlang Resource Type representing a
 * cairo_path_t
 * @brief cairo_surface_t_RT
 */
static ErlNifResourceType *cairo_font_options_t_RT = NULL;

/**
 * Struct to use in place of cairo_surface_t when
 * allocating resources with enif_alloc_resource
 */
typedef struct {
    cairo_font_options_t *data;
} cairo_font_options_t_TYPE;

/**
 * Destructor function to enable garbage collection of
 * cairo_surface_t instances
 * @brief gc_cairo_surface_t
 * @param env Erlang environment
 * @param instance wraps a cairo_surface_t instance
 */
static void gc_cairo_font_options_t (ErlNifEnv *env, void *instance) {
    cairo_font_options_t_TYPE* opts = (cairo_font_options_t_TYPE *) instance;
    if (env && opts && opts->data) {
        cairo_font_options_destroy(opts->data);
    }
}

// --------------------------------------------------------------------------------

// cairo_pattern_t
// --------------------------------------------------------------------------------

/**
 * Erlang Resource Type representing a
 * cairo_pattern_t
 * @brief cairo_pattern_t_RT
 */
static ErlNifResourceType *cairo_pattern_t_RT = NULL;

/**
 * Struct to use in place of cairo_surface_t when
 * allocating resources with enif_alloc_resource
 */
typedef struct {
    cairo_pattern_t *data;
} cairo_pattern_t_TYPE;

/**
 * Destructor function to enable garbage collection of
 * cairo_surface_t instances
 * @brief gc_cairo_surface_t
 * @param env Erlang environment
 * @param instance wraps a cairo_surface_t instance
 */
static void gc_cairo_pattern_t (ErlNifEnv *env, void *instance) {
    cairo_pattern_t_TYPE* p = (cairo_pattern_t_TYPE *) instance;
    if (env && p && p->data) {
        cairo_pattern_destroy(p->data);
    }
}

// --------------------------------------------------------------------------------


// cairo_region_t
// --------------------------------------------------------------------------------

/**
 * Erlang Resource Type representing a
 * cairo_region_t
 * @brief cairo_region_t_RT
 */
static ErlNifResourceType *cairo_region_t_RT = NULL;

/**
 * Struct to use in place of cairo_region_t when
 * allocating resources with enif_alloc_resource
 */
typedef struct {
    cairo_region_t *data;
} cairo_region_t_TYPE;

/**
 * Destructor function to enable garbage collection of
 * cairo_surface_t instances
 * @brief gc_cairo_surface_t
 * @param env Erlang environment
 * @param instance wraps a cairo_surface_t instance
 */
static void gc_cairo_region_t (ErlNifEnv *env, void *instance) {
    cairo_region_t_TYPE* r = (cairo_region_t_TYPE *) instance;
    if (env && r && r->data) {
        cairo_region_destroy(r->data);
    }
}

// --------------------------------------------------------------------------------
