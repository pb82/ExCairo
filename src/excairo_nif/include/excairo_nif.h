#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "erl_nif.h"
#include "cairo.h"

#define MAX_FILENAME_LENGTH 255
#define MAX_FONTFMLY_LENGTH 32
#define MAX_TEXT_SIZE 512

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


// Standard return type
#define ERL_MAKE_OK_TUPLE(data) enif_make_tuple2(env, enif_make_atom(env, "ok"), data);
#define ERL_OK enif_make_atom(env, "ok");

// Use only in nif initializer function
#define ERL_ASSERT_LOAD(condition) if (!(condition)) return -1

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
