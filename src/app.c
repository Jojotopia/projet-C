/**
 * @file app.c
 *
 * @author     Groupe J
 * @date       2021
 * @copyright  BSD 3-Clause License
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "./rules.h"

int main(int argc, char **argv) {
  char *rules_argument = NULL;
  char *facts_argument = NULL;
  char *output_argument = NULL;
  int c;
  // option is already defined in other library so can't start by '_'
  struct option long_opt[] = {
    {"rules", required_argument, NULL, 'r'},
    {"facts", required_argument, NULL, 'f'},
    {"output", required_argument, NULL, 'o'},
    {"help", no_argument, NULL, 'h'},
    {NULL, 0, NULL, 0  }
  };

  while ((c = getopt_long(argc, argv, "", long_opt, NULL)) != -1) {
    switch (c) {
      case -1:
      case 0:
        break;

      case 'f':
        facts_argument = optarg;
        break;

      case 'r':
        rules_argument = optarg;
        break;

      case 'o':
        output_argument = optarg;
        break;

      case 'h':
        printf("Usage: %s [OPTIONS]\n", argv[0]);
        printf("  --facts                   file which contains facts\n");
        printf("  --rules                   file which contains rules\n");
        printf("  --output                  file which contains output\n");
        printf("  --help                    print this help and exit\n");
        printf("\n");
        return(0);

      default:
        return(-2);
    }
  }

  if (rules_argument == NULL ||
      facts_argument == NULL ||
      output_argument == NULL) {
    fprintf(stderr, "Usage src/rules: --rules <rules_file>");
    fprintf(stderr, " --facts <facts_file> --output <output_file>\n");

  } else {
    FILE *rules_file = fopen(rules_argument, "r");
    FILE *facts_file = fopen(facts_argument, "r");
    FILE *output_file = fopen(output_argument, "w");

    if (!rules_file) {
      fprintf(stderr, "rules file can't be opened\n");
    } else if (!facts_file) {
      fprintf(stderr, "facts file can't be opened\n");
    } else if (!output_file) {
      fprintf(stderr, "output file can't be opened or created\n");
    } else {
      int *facts = malloc(0);
      int facts_count = 0;

      // Reading of the facts file and registration of values
      // in an int array
      int turn = 0;
      int tmp_fact = -1;
      while (turn == 0) {
        char entry = fgetc(facts_file);
        if (entry == -1) {
          if (tmp_fact != -1) {
            facts = realloc(facts, (facts_count + 1) * (sizeof(int)));
            facts_count += 1;
            facts[facts_count - 1] = tmp_fact;
            tmp_fact = -1;
          }
          turn = 1;
        } else if (entry != 32 && entry != 10) {
          if (entry >= 48 && entry <= 57) {
            if (tmp_fact == -1) {
              tmp_fact = atoi(&entry);
            } else {
              tmp_fact = concat(tmp_fact, atoi(&entry));
            }
          } else {
            char *output = "Some caracters are not numbers in facts file !";
            fwrite(output, sizeof(output[0]), strlen(output), output_file);
            free(facts);
            fclose(rules_file);
            fclose(facts_file);
            fclose(output_file);
            return 0;
          }
        } else if (entry == 32) {
            facts = realloc(facts, (facts_count + 1) * (sizeof(int)));
            facts_count += 1;
            facts[facts_count - 1] = tmp_fact;
            tmp_fact = -1;
        }
      }

      RuleList *rules = rule_list_create();
      char output[1000000] = "";

      // Reading of the rule file and registration of rules
      // in rules array
      turn = 0;
      int line_jump = 0;  // Say the number of line_jump past
      Rule *tmp = rule_create();
      int previous_line_useful = 0;
      int tmp_constraint = -1;
      while (turn == 0) {
        char entry = fgetc(rules_file);

        // A caracter but not space or line_jump or end of file
        if (entry != 32 && entry != 10 && entry != -1) {
          if (entry >= 48 && entry <= 57) {
            if (tmp_constraint == -1) {
              tmp_constraint = atoi(&entry);
            } else {
              tmp_constraint = concat(tmp_constraint, atoi(&entry));
            }
            previous_line_useful = 1;
          } else {
            char *output = "Some caracters are not numbers in rules file !";
            fwrite(output, sizeof(output[0]), strlen(output), output_file);
            free(facts);
            rule_list_destroy(rules);
            rule_destroy(tmp);
            fclose(rules_file);
            fclose(facts_file);
            fclose(output_file);
            return 0;
          }
        } else if (entry == 32 || entry == 10 || entry == -1) {
          if (tmp_constraint != -1) {
            if (line_jump == 0) {
              rule_add_constraint(tmp, tmp_constraint);
            } else if (line_jump == 1) {
              rule_add_result(tmp, tmp_constraint);
            }
            tmp_constraint = -1;
          }
        }
        if (entry == 10 || entry == -1) {  // a line_jump or a end of file
          line_jump += 1;
          if (previous_line_useful == 3) {
            char *output = "Too much line jump in rules file !";
            fwrite(output, sizeof(output[0]), strlen(output), output_file);
            free(facts);
            rule_list_destroy(rules);
            rule_destroy(tmp);
            fclose(rules_file);
            fclose(facts_file);
            fclose(output_file);
            return 0;
          }
          if (line_jump >= 3) {
            line_jump = 0;
            rule_list_add_rule(rules, rule_clone(tmp));
            rule_destroy(tmp);
            tmp = rule_create();
          }
          if (entry == -1) {
            if (line_jump >= 2) {
              rule_list_add_rule(rules, rule_clone(tmp));
              rule_destroy(tmp);
              tmp = rule_create();
            }
            turn = 1;
          }
          previous_line_useful += 1;
        }
      }
      rule_destroy(tmp);

      rules_check(facts, facts_count, rules, output);

      char *export = malloc(0);
      unsigned int h = 0;
      size_t export_size = 0;
      while (output[h] != 0) {
        export_size += 1;
        export = realloc(export, export_size);
        export[h] = output[h];
        h++;
      }

      // Writing in the output file
      if (fwrite(export, sizeof(export[0]), h, output_file) == h) {
        printf("Output : %s\n", output);
      } else {
        printf("The registration in the output file failed !");
      }

      free(export);

      fclose(rules_file);
      fclose(facts_file);
      fclose(output_file);
    }
  }
  return EXIT_SUCCESS;
}
