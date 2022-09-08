/**
 * @file test-delete-rule.c
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

  Rule *rule2 = rule_create();
  rule_add_constraint(rule2, 4);
  rule_add_constraint(rule2, 5);
  rule_add_result(rule2, 6);

  RuleList *rules = rule_list_create();

  rule_list_add_rule(rules, rule);
  rule_list_add_rule(rules, rule2);

  assert(rules->count = 2);

  assert(rules->rules[0]->constraints[0] == 1);
  assert(rules->rules[0]->constraints[1] == 2);
  assert(rules->rules[0]->results[0] == 3);

  rules = rule_list_delete_rule(rules, 0);
  assert(rules->count = 1);

  assert(rules->rules[0]->constraints[0] == 4);
  assert(rules->rules[0]->constraints[1] == 5);
  assert(rules->rules[0]->results[0] == 6);

  rule_list_destroy(rules);

  return EXIT_SUCCESS;
}
