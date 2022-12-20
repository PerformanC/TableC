# TableC

Advanced and portable closed-addressing hashtable implementation for C.

## Features

TableC was made with portability, performance and stability in mind, so it might leak in a high-level API, but we have everything you will need to:

- [x] Set keys and values
- [x] Get values based on the key
- [x] Remove keys and values

I don't plan on having a high-level API, so it will stay simple, but it will be powerful.

## Performance

TableC has a high performance, but it was focused on portability and stability, so for now, there aren't a lot of optimizations, but we are working on it. For now, we are making sure it's stable and portable.

Want to get fancy? Here are some benchmarks on running on a `i3 CPU, 2 cores, 4 threads with 8GB RAM ddr4, using Alpine` system:

| Samples | Repetitions (stabilization) | Time per sample |
| ------- | --------------------------- | --------------- |
| 1000    | 10000                       | 0.000561s       |
| 10000   | 1000                        | 0.001759s       |
| 100000  | 100                         | 0.049271s       |

**Those results are not manipulated**, but they shouldn't be taken as a reference, since they are not using compiler optimization flags, and nor being run in an isolated environment, they are good enough to show that TableC is impressively fast for a new library.

## Usage

TableC comes with a simple API, but it's powerful, take a look at the example below of using TableC:

```c
/* First we need to include the tablec.h header file, so we can use TableC's functions. */
#include "tablec.h"

/* Here we are initializing the hastable, so we can use the buckets. */
struct hashtable *tablec;
tablec_init(&tablec, 1);

/* Here we are setting a key and a value, so we can get it later. */
tablec_set(&tablec, "key", "value");

/* Here we are getting the value based on the key. */
char *value = tablec_get(&tablec, "key");

printf("Found: %s\n", value);

/* Since we are going to need more space, we are expanding the hashtable, so we can add more keys into it. */
tablec_expand(&tablec, 2);

/* Now we have more space, so we can set more keys into it. */
tablec_set(&tablec, "key2", "value2");

char *value2 = tablec_get(&tablec, "key2");

printf("Found: %s\n", value2);

/* Now we are removing the key2, so we can have one more empty space into the bucket. */
tablec_del(&tablec, "key2");

/* Now we can set another key into the hashtable. */
tablec_set(&tablec, "key3", "value3");

char *value3 = tablec_get(&tablec, "key3");

printf("Found: %s\n", value3);

/* Now we are going to deallocate the tablec, so no memory leaks happen. */
tablec_cleanup(&tablec);
```

## Docs

TableC has an awesome documentation in the [guides folder](guides/en-us/about.md), with hand-writing documentation, so you can learn how to use TableC, and how it works, each function is explained in detail, so you can understand how it works, and how to use it.

## Why TableC?

We are making TableC because we need a simple, portable and still lightweight hashtable implementation for C, so we decided to make it, and we are going to keep it updated, so it can be used in more projects.

TableC is fast, portable, simple and with no known bugs, till now.

## Contributing

We are open to contributions, and happy with them, but before opening a pull request, please look if the pull request matches the [contributing](CONTRIBUTING.md) file](CONTRIBUTING.md), and if it does, feel free to open a pull request, and we will review it as soon as possible.

## Support

If you want to talk about anything related to a PerformanC's project, or anything, especially programming, you can join our [Discord server](https://discord.gg/uPveNfTuCJ), and talk with us, we are always open to talk about anything, and we will help you with any issues and questions.

## License

TableC is licensed under the MIT License, so you can use it in any project, even commercial ones, what so ever, TableC can't be used for AI training of any kind.

## Projects using TableC

Because TableC is a new library, it is not used in a lot of projects, but feel free to use TableC in one of your projects and make a PR to add it here.

[Experimental] [Coglink](https://github.com/PerformanC/Coglink) by PerformanC (developer of TableC)

* Feito com :heart: por um Brasileiro! 🇧🇷