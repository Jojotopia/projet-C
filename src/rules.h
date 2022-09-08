/**
 * @file rules.h
 *
 * @author     Groupe J
 * @date       2021
 * @copyright  BSD 3-Clause License
 */
#ifndef RULES_H_
#define RULES_H_

#include <stdio.h>
#include <stdlib.h>

/**
 * Rule _Rule Type.
 * define the Rule type
 */
typedef struct _Rule Rule;

/**
 * RuleList _RuleList Type.
 * define the RuleList type
 */
typedef struct _RuleList RuleList;


/**
 * rule_create create a Rule.
 *
 * @return the Rule created
 */
extern Rule *rule_create(void);

/**
 * rule_erase reset a rule.
 *
 * @param rule the rule to reset
 *
 * @return the rule without any constraints and without any results
 */
extern Rule *rule_erase(Rule *rule);

/**
 * rule_destroy free the rule.
 *
 * @param rule the rule to free
 */
extern void rule_destroy(Rule *rule);

/**
 * rule_add_constraint add a constraint to a Rule.
 *
 * @param rule the rule to add constraint
 * @param constraint int constraint to add
 *
 * @return the rule with the new constraint
 */
extern Rule *rule_add_constraint(Rule *rule, int constraint);

/**
 * rule_add_result add a result to a Rule.
 *
 * @param rule the rule to add result
 * @param result int result to add
 *
 * @return the rule with the new Result
 */
extern Rule *rule_add_result(Rule *rule, int result);

/**
 * rule_clone clone a rule.
 *
 * @param src the rule to clone
 *
 * @return a new Rule wich have same values as src
 */
extern Rule *rule_clone(Rule *src);


/**
 * rule_list_create create a rule_list.
 *
 * @return the rule_list created
 */
extern RuleList *rule_list_create(void);

/**
 * rule_list_erase reset a rule_list.
 *
 * @param rule_list the rule_list to reset
 *
 * @return the rule_list without any rule
 */
extern RuleList *rule_list_erase(RuleList *rule_list);

/**
 * rule_list_destroy free the rule_list.
 *
 * @param rule_list the rule_list to free
 */
extern void rule_list_destroy(RuleList *rule_list);

/**
 * rule_list_add_rule add a rule in a rule_list.
 *
 * @param rule_list a list of Rule where the Rule will be added
 * @param rule the Rule to add
 *
 * @return the rule_list with the new rule
 */
extern RuleList *rule_list_add_rule(RuleList *rule_list, Rule *rule);

/**
 * rule_list_delete_rule delete a rule in a rule_list.
 *
 * @param rule_list a list of Rule which contain the rule to be delete
 * @param ruleId the id of rule which will be deleted
 *
 * @return the rule_list without the deleted rule
 */
extern RuleList *rule_list_delete_rule(RuleList *rule_list, int ruleId);

/**
 * rules_check carries out deduction by a front chaining system.
 *
 * @param facts an integer array
 * @param facts_count the count of values in facts
 * @param rule_list a list of Rule
 * @param output the output string
 *
 * @return the result of the deduction by a front chaining system
 *
 * @note the output is limited at 1 000 000 characters
 */
extern void rules_check(int *facts,
                        int facts_count,
                        RuleList *rule_list,
                        char *output);
/**
 * concat concatenates two integer numbers.
 *
 * @param x first integer
 * @param y second integer
 *
 * @return the concatenation of x and y
 *
 * @note if x = 0 the result will be y
 */
extern int concat(int x, int y);

#endif  // RULES_H_
