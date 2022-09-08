/**
 * @file test-erase-rule.c
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
  rule_add_constraint(rule, 1);
  rule_add_constraint(rule, 2);
  rule_add_result(rule, 3);

  assert(rule->constraints_count == 2);
  assert(rule->results_count == 1);

  rule = rule_erase(rule);

  assert(rule->constraints_count == 0);
  assert(rule->results_count == 0);

  rule_destroy(rule);

  return EXIT_SUCCESS;
}
