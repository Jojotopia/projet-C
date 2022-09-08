/**
 * @file test-rules-check.c
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

  Rule *rule3 = rule_create();
  rule_add_constraint(rule3, 3);
  rule_add_result(rule3, 7);

  RuleList *rules = rule_list_create();

  rule_list_add_rule(rules, rule);
  rule_list_add_rule(rules, rule2);
  rule_list_add_rule(rules, rule3);

  int *facts = malloc(2*sizeof(int));
  facts[0] = 1;
  facts[1] = 2;
  int facts_count = 2;
  char output[100] = "";

  rules_check(facts, facts_count, rules, output);

  assert(strcmp(output, "1 2 3 7 ") == 0);

  return EXIT_SUCCESS;
}
