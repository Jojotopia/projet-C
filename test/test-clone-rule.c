/**
 * @file test-clone.c
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

  Rule *clone = rule_clone(rule);

  assert(clone->constraints_count == rule->constraints_count);
  assert(clone->results_count == rule->results_count);

  assert(clone->constraints[0] == rule->constraints[0]);
  assert(clone->constraints[1] == rule->constraints[1]);
  assert(clone->results[0] == rule->results[0]);

  rule_destroy(rule);
  rule_destroy(clone);

  return EXIT_SUCCESS;
}
