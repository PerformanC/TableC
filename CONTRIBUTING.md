# Contributions

## Before opening a pull request

In all PerformanC projects, we make sure that the code is clean and consistent, to be sure of that we have some guidelines when you are contributing to The TableC Project, here is a list of some of the guidelines, but remember to make a good and clean code, and according to our indentation:

* Make sure that you are committing to the latest version.

* You must use the same indentation as the rest of the project, follow the next section for information.

* (OPTIONAL) Update the documentation if you change a function parameter.

## Code indentation

PerformanC uses its own indentation, which uses a 2-space indentation, using C89.

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

  while (variable == 0) {
    printf("Hello World!\n");
    variable = 1;
  }

  return;
}
```

## Code comments

We don't allow code comments, but any comment can be done on the documentation, as it says how the functions work, one per one.
