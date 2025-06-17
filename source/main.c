// Purpose: Knapsack in C!
// Author: Almog Sharon (16.6.2025)

#include "common.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct item_s
{
  uint32_t weight;
  uint32_t value;
} item_t;

return_code_t max_value(item_t items[], size_t length, size_t max_weight,
                        uint32_t *value)
{
  return_code_t return_code = RETURN_CODE_UNINITIALIZED;
  uint32_t **dp_table = NULL;
  uint32_t with = 0;
  uint32_t without = 0;
  uint32_t better_value = 0;

  ON_TRUE_SET_AND_GO_TO_CLEANUP(((value) == NULL), return_code,
                                RETURN_CODE_BAD_VALUE);

  CALLOC_OR_FAIL(dp_table, length + 1, return_code, RETURN_CODE_CALLOC_ERROR);

  for (size_t index = 0; index <= length; index++)
  {
    CALLOC_OR_FAIL(dp_table[index], max_weight + 1, return_code,
                   RETURN_CODE_CALLOC_ERROR);
  }

  for (size_t index = 1; index <= length; index++)
  {
    for (uint32_t weight = 0; weight <= max_weight; weight++)
    {
      if (items[index - 1].weight > weight)
      {
        dp_table[index][weight] = dp_table[index - 1][weight];
        continue;
      }

      without = dp_table[index - 1][weight];
      with = dp_table[index - 1][weight - items[index - 1].weight] +
             items[index - 1].value;

      better_value = (with > without) ? with : without;
      dp_table[index][weight] = better_value;
    }
  }

  *value = dp_table[length][max_weight];
  return_code = RETURN_CODE_SUCCESS;

l_cleanup:
  if (dp_table != NULL)
  {
    for (size_t index = 0; index <= length; index++)
    {
      FREE(dp_table[index]);
    }
    FREE(dp_table);
  }
  return return_code;
}

int main()
{
  return_code_t return_code = RETURN_CODE_UNINITIALIZED;
  uint32_t value = 0;
  item_t items[] = {
      {.weight = 5, .value = 10},
      {.weight = 4, .value = 40},
      {.weight = 6, .value = 30},
      {.weight = 4, .value = 50}};

  return_code = max_value(items, ARRLEN(items), 10, &value);
  CLEANUP_ON_FAIL(return_code);
  (void)printf("Max value: %d\n", value);
l_cleanup:
  return return_code;
}
