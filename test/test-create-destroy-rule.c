/**
 * @file test-create-destroy-rule.c
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
  Rule *rule = rule_create();
  assert(rule->constraints_count == 0);
  assert(rule->results_count == 0);
  rule_destroy(rule);

  return EXIT_SUCCESS;
}
