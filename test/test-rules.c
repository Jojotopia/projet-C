/**
 * @file test-rules.c
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
  assert(rule->results_count == 0);
  rule_add_constraint(rule, 1);
  rule_add_constraint(rule, 2);
  rule_add_result(rule, 3);

  RuleList *rules = rule_list_create();

  rule_list_add_rule(rules, rule_clone(rule));

  assert(rules->count == 1);
  assert(rules->rules[0]->constraints[0] == 1);
  assert(rules->rules[0]->constraints[1] == 2);
  assert(rules->rules[0]->results[0] == 3);

  rule_list_add_rule(rules, rule_clone(rule));

  assert(rules->count == 2);
  assert(rules->rules[1]->constraints[0] == 1);
  assert(rules->rules[1]->constraints[1] == 2);
  assert(rules->rules[1]->results[0] == 3);

  rules = rule_list_delete_rule(rules, 1);
  assert(rules->count == 1);
  rules = rule_list_delete_rule(rules, 0);
  assert(rules->count == 0);

  rule_list_destroy(rules);
  rule_destroy(rule);

  return EXIT_SUCCESS;
}
