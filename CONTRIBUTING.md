# Contributions

## Before opening a pull request

In PerformanC projects, we are always trying to make the code consistent, principally the code syntax, for this, we have some guidelines when you are contributing to The TableC Project, here is a list of some of the guidelines, but remember to make a good and clean code:

* Be sure that the version that you are going to commit the changes to is the latest, if not, conflicts may cause your PR to be not accepted.

* You need to use the same syntax and style from the test of the project, in any questions, follow to the next section.

* Make sure to run Fuzzy Benchmarking testing and Special Cases testing before opening a pull request, those will be as well asked in the PR template.

* This one is optional, but when editing a parameter of a function, or even changing the way a function works, make sure to update in the docs.

## Code syntax and style

TableC uses its own syntax, which uses a 2-space indentation, and the code MUST have compatibility of at least C99+, breaking support of newer versions of C is not allowed. 

The example below is an example of using TableC's syntax:

```c
void function(void) {
  start:

  size_t variable = 0;

  if (variable == 0) variable = 1;
  else variable = 0;

  /* In case you need to make more than one function in a if: */
  
  if (variable == 0) {
    printf("Hello World!\n");
    return;
  } else {
    variable = 2;
    goto start;
  }

  do {
    printf("Hello World!\n");
    variable = 1;
  } while (variable == 0);

  return;
}
```

## Code comments

The TableC Project has 2 main languages, English and Portuguese from Brazil, those languages can be used anywhere on the project, but only English can be used for variable names, function names, and parameters, and only Portuguese from Brazil can be used, other ones like Portuguese from Portugal or Spanish will not be accepted.
