/**
 * @file test-erase-rule-list.c
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

  RuleList *rules = rule_list_create();

  rule_list_add_rule(rules, rule);

  assert(rules->count == 1);

  rules = rule_list_erase(rules);

  assert(rules->count == 0);

  rule_list_destroy(rules);

  return EXIT_SUCCESS;
}
