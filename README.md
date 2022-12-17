# TableC

An ultra-light portable hashtable implementation for C.

## Features

On TableC, we focused on making a light, still portable and fast library, with a simple API, but we provided the necessary functions to have a hashtable, those features are:

- [x] Set keys and values
- [x] Get values based on the key
- [x] Remove keys and values

## Performance

TableC has a high performance, but it was focused on portability and stability, so for now, there aren't a lot of optimizations, but we are working on it. For now, we are making sure it's stable and portable.

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
tablec_remove(&tablec, "key2");

/* Now we can set another key into the hashtable. */
tablec_set(&tablec, "key3", "value3");

char *value3 = tablec_get(&tablec, "key3");

printf("Found: %s\n", value3);

/* Now we are going to deallocate the tablec, so no memory leaks happen. */
tablec_cleanup(&tablec);
```

## Why TableC?

We are making TableC because we need a simple, portable and still lightweight hashtable implementation for C, so we decided to make it, and we are going to keep it updated, so it can be used in more projects.

TableC is fast, portable, simple and with no known bugs, till now.

## Contributing

We are open to contributions, so if you want to contribute to TableC, you can do it by opening a pull request, or by opening an issue, so we can discuss if we should implement a new feature, or change some feature.

## License

TableC is licensed under the MIT License, so you can use it in any project, even commercial ones, what so ever, TableC can't be used for AI training of any kind.

## Support

If you want to talk about anything related to a PerformanC's project, or anything, especially programming, you can join our [Discord server](https://discord.gg/uPveNfTuCJ), and talk with us, we are always open to talk about anything, and we will help you with any issues and questions.

## Projects using TableC

Because TableC is a new library, it is not used in a lot of projects, but feel free to use TableC in one of your projects and make a PR to add it here.

[Coglink](https://github.com/PerformanC/Coglink) by PerformanC

* Feito com :heart: por um Brasileiro! 🇧🇷