/**
 * @file rules.c
 *
 * @author     Groupe J
 * @date       2021
 * @copyright  BSD 3-Clause License
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./rules.h"

#include "./rules.inc"

Rule *rule_create(void) { return calloc(1, sizeof(Rule)); }

Rule *rule_erase(Rule *rule) {
  if (rule->constraints_count != 0) {
    free(rule->constraints);
    rule->constraints_count = 0;
  }
  if (rule->results_count != 0) {
    free(rule->results);
    rule->results_count = 0;
  }
  return memset(rule, 0, sizeof(rule));
}

void rule_destroy(Rule *rule) {
  rule_erase(rule);
  free(rule);
}

Rule *rule_add_constraint(Rule *rule, int constraint) {
  rule->constraints =
      realloc(rule->constraints, (rule->constraints_count + 1) * sizeof(int));
  rule->constraints_count += 1;
  rule->constraints[rule->constraints_count - 1] = constraint;
  return rule;
}

Rule *rule_add_result(Rule *rule, int result) {
  rule->results =
      realloc(rule->results, (rule->results_count + 1) * sizeof(int));
  rule->results_count += 1;
  rule->results[rule->results_count - 1] = result;
  return rule;
}

Rule *rule_clone(Rule *src) {
  Rule *dest = rule_create();
  for (unsigned int i = 0; i < src->constraints_count; i++) {
    rule_add_constraint(dest, src->constraints[i]);
  }
  for (unsigned int i = 0; i < src->results_count; i++) {
    rule_add_result(dest, src->results[i]);
  }
  return dest;
}

RuleList *rule_list_create(void) { return calloc(1, sizeof(RuleList)); }

RuleList *rule_list_erase(RuleList *rule_list) {
  for (unsigned int i = 0; i < rule_list->count; i++) {
    rule_destroy(rule_list->rules[i]);
  }
  free(rule_list->rules);
  rule_list->count = 0;
  return memset(rule_list, 0, sizeof(rule_list));
}

void rule_list_destroy(RuleList *rule_list) {
  if (rule_list->count != 0) {
    rule_list_erase(rule_list);
  }
  free(rule_list);
}

RuleList *rule_list_add_rule(RuleList *rule_list, Rule *rule) {
  rule_list->rules =
      realloc(rule_list->rules, (rule_list->count + 1) * sizeof(Rule *));
  rule_list->count += 1;
  rule_list->rules[rule_list->count - 1] = rule;
  return rule_list;
}

RuleList *rule_list_delete_rule(RuleList *rule_list, int ruleId) {
  if (rule_list->count == 0) {
    return NULL;
  } else if (rule_list->count == 1) {
    return rule_list_erase(rule_list);
  } else {
    RuleList *newRuleList = rule_list_create();
    for (unsigned int g = 0; g < rule_list->count; g++) {
      if (g != ruleId) {
        Rule *newRule = rule_create();
        for (unsigned int y = 0; y < rule_list->rules[g]->constraints_count;
             y++) {
          rule_add_constraint(newRule, rule_list->rules[g]->constraints[y]);
        }
        for (unsigned int y = 0; y < rule_list->rules[g]->results_count; y++) {
          rule_add_result(newRule, rule_list->rules[g]->results[y]);
        }
        rule_list_add_rule(newRuleList, newRule);
      }
    }
    rule_list_destroy(rule_list);

    return newRuleList;
  }
}

void rules_check(int *facts,
                 int facts_count,
                 RuleList *rule_list,
                 char *output) {
  char tmp_output[1000000] = "";

  // Writing of initials facts in tmp_output string
  for (unsigned int i = 0; i < facts_count; i++) {
    char tmp[2*sizeof(int)];
    snprintf(tmp, 3*sizeof(int), "%d", facts[i]);
    snprintf(tmp_output + strlen(tmp_output),
             sizeof(tmp_output) + sizeof(tmp),
             "%s ",
             tmp);
  }

  // A rule is to delete if this variable is not equals to -1
  int rules_to_delete = -1;

  for (unsigned int i = 0; i < rule_list->count; i++) {
    for (unsigned int k = 0; k < facts_count; k++) {
      if (rule_list->count > 0) {
        if (rules_to_delete != -1) {
          rule_list = rule_list_delete_rule(rule_list, rules_to_delete);
          if (rule_list->count == 0) {
            break;
          }
          rules_to_delete = -1;
        }
        if (facts[k] == rule_list->rules[i]->constraints[0]) {
          unsigned int correct_facts = 0;
          unsigned int facts_check = 0;
          for (unsigned int l = 0; l < rule_list->rules[i]->constraints_count;
               l++) {
            if (k + facts_check < facts_count) {
              if (rule_list->rules[i]->constraints[l]
                  == facts[k + facts_check]) {
                correct_facts += 1;
                facts_check += 1;
              }
            }
          }
          if (correct_facts != rule_list->rules[i]->constraints_count) {
            facts_check = 1;
            for (unsigned int l = 0; l < rule_list->rules[i]->constraints_count;
                 l++) {
              if (k >= facts_check) {
                if (rule_list->rules[i]->constraints[l]
                    == facts[k - facts_check]) {
                  correct_facts += 1;
                  facts_check += 1;
                }
              }
            }
          }

          if (correct_facts == rule_list->rules[i]->constraints_count) {
            // Writing of all results of th rule
            for (unsigned j = 0; j < rule_list->rules[i]->results_count; j++) {
              char *tmp_char = malloc(sizeof(rule_list->rules[i]->results[j]));
              snprintf(tmp_char,
                       sizeof(tmp_char),
                       "%d",
                       rule_list->rules[i]->results[j]);
              if (strstr(tmp_output, tmp_char) == NULL) {
                snprintf(tmp_output + strlen(tmp_output),
                         sizeof(tmp_output) +
                         sizeof(rule_list->rules[i]->results[j])
                         , "%d ", rule_list->rules[i]->results[j]);
                facts = realloc(facts, (facts_count + 1) * (sizeof(int)));
                facts[facts_count] = rule_list->rules[i]->results[j];
                facts_count += 1;
              }
              free(tmp_char);
            }
            unsigned int m = i;
            rules_to_delete = m;
            i = 0;
            k = -1;
          }
        }
      }
    }
  }
  free(facts);
  rule_list_destroy(rule_list);
  snprintf(output + strlen(output), sizeof(output) + sizeof(tmp_output), "%s",
           tmp_output);
}

int concat(int x, int y) {
  if (y == 0) {
    return x*10;
  } else {
    int temp = y;
    while (y > 0) {
      x *= 10;
      y /= 10;
    }
    return x + temp;
  }
}
