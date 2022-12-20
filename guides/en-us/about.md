# About TableC

TableC is an implementation of hashtables C, providing an easy API, with a simple and fast implementation. It is a header-only library, so you can just include the header file and use it. It also uses the closed-addressing approach for dealing with collisions.

## Why closed-addressing?

The closed-addressing has some advantages over the open-addressing, which made me decide to choose closed-addressing over open-addressing, the most famous and most used one.

One of them is that the closed-addressing use fewer `strcmp`s that are not worth the time, because the index of a key can be near that key, making it `strcmp`s a key that is not even close to the key you are looking for.

Another is that the closed-addressing is an approach that would end up being a better design, because it is easier to implement, and it is easier to understand (for **me**).

## Systems used by TableC

Tablec is smart, and it uses a lot of features and codes to improve its performance, some of them are:

*  Uses an empty slot array to list slots that are empty so they can be fastly accessed and re-used.
*  Saves the length and capacity of the empty slots array from the hashtable, so it can be fastly read, written, and deleted.

Those seem small systems, but I work hard on them so they can work fastly and efficiently.

## How stable is TableC?

TableC is NOT stable, since because it was not tested enough, but some tests (made by me, especially to TableC) are passing, and I am working on it to make it stable.

The following functions are hardly tested, using Fuzzy testing and with special cases to see how it handles them:

*  `tablec_get`
*  `tablec_set`
*  `tablec_del`

## Why no contains function?

TableC was made for high portability, but also performance and those functions are not needed, since you can use `tablec_get` to check if a key exists, and if it returns `NULL`, then it does not exist, removing the necessity of using 2 functions that lookup through the hashtable to retrieve the value.

## TableC misses some features

TableC misses some features because I am focusing on the main functions, like `tablec_get`, which I hardly try to optimize, and adding more features doesn't mean a better library, if they are not well done, and I am working on it to make it better.

## TableC isn't stable, why should I use it?

That's the point, you should not use it for now, till more testing is done, but when the tests are done, you will be able to use it, and it will be stable, and you will be able to use it in your projects, allowing to use a powerful hashtable library, with a simple API, and a fast implementation.

## How to use TableC

In the guides folder, there will be a set of guides on how to use each of its functions, you can see them, and use them in your projects. And also the tests folder, there will be a set of tests used to test TableC, and you can use some of its code in your projects.

## How to pronounce TableC

Funny section, TableC is not pronounced as you think it is, you can pronounce it the same way you do with "Tables", but with a `C` and the end to represent the C language, and also to replace the `s` character which makes `Tables` not be only one, but multiple, because this is how a hashtable is.