# Contributions

## Before opening a pull request

Before you open a pull request, there are a few things you need to make sure to do.

* Make sure that the version that you edited was the latest, or else there are chances of creating a merge conflict, and ending up having your pull request declined.
* Make sure that you are using the same code style as the rest of the project, if you are using a different code style, your pull request will be declined.
* Make sure that you are not breaking any of the tests, if you are, your pull request will be declined.
* If you edited one of the parameters of a function, make sure you updated the guides, but this is optional.
* You must run the fuzzy benchmarking, to compare how the performance of the library changed, this is important for us when deciding if the PR will be accepted.

## Code syntax and style

TableC uses my syntax, which uses 2 spaces identation, the syntax of the added code MUST match the syntax of the rest of the project, see an example below:

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

The code comments MUST be in either English or Portuguese (BR), if you are using a different language, your pull request won't be declined, but it will be asked for you to translate for one of those languages.

## Main (not programming) languages

The main languages of TableC are Portuguese and English, but Portuguese is limited to only comments.

In case you don't speak any of those languages, you can use tools like Google translator to translate, but you must make sure that the translation is correct, and that it is understandable.