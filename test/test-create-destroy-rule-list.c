/**
 * @file test-create-destroy-rule-list.c
 *
 * @author     Groupe J
 * @date       2021
 * @copyright  BSD 3-Clause License
 */

#ifdef NDEBUG
#undef NDEBUG
#endif
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "./rules.h"

#include "./rules.inc"

int main(void) {
  RuleList *rulelist = rule_list_create();
  assert(rulelist->count == 0);
  rule_list_destroy(rulelist);

  return EXIT_SUCCESS;
}
