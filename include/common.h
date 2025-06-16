// Purpose: common things for many projects
// Author: Almog Sharon

#include <stdlib.h>
#include <string.h>

typedef enum {
  RETURN_CODE_SUCCESS = 0,
  RETURN_CODE_UNINITIALIZED = 1,
  RETURN_CODE_BAD_VALUE,
  RETURN_CODE_CALLOC_ERROR
} return_code_t;

#define ARRLEN(x) ((sizeof((x))) / (sizeof((x)[0])))

#define ON_TRUE_SET_AND_GO_TO_CLEANUP(condition, return_code, new_return_code) \
  do {                                                                         \
    if ((condition)) {                                                         \
      (return_code) = (new_return_code);                                       \
      goto l_cleanup;                                                          \
    }                                                                          \
  } while (0)

#define CLEANUP_ON_FAIL(return_code)                                           \
  do {                                                                         \
    if ((return_code) != RETURN_CODE_SUCCESS) {                                \
      goto l_cleanup;                                                          \
    }                                                                          \
  } while (0)

#define CALLOC_OR_FAIL(ptr, len, return_code, new_return_code)                 \
  do {                                                                         \
    (ptr) = calloc((len), sizeof(*(ptr)));                                     \
    if ((ptr) == NULL) {                                                       \
      (return_code) = (new_return_code);                                       \
      goto l_cleanup;                                                          \
    }                                                                          \
  } while (0)

#define FREE(ptr)                                                              \
  do {                                                                         \
    if ((ptr) != NULL) {                                                       \
      free((ptr));                                                             \
      (ptr) = NULL;                                                            \
    }                                                                          \
  } while (0)
