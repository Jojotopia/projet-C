struct _Rule {
  int *constraints;
  int constraints_count;
  int *results;
  int results_count;
};

struct _RuleList {
  int count;
  Rule **rules;
};
