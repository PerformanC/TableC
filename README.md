# TableC

Low-level C89 Closed/Open-addressed hashtable implementation.

## Branch info

This branch is marked as a secondary branch, using an open-addressing approach with no internal dynamic allocations. This is a mirror of the open-addressing branch (secondary branch) but with no mallocs. (fastest branch)

## Features

- [x] Expandable hashtable
- [x] Overflow protected
- [x] No memory leaks
- [x] C89 compatible

## Performance

Here's a benchmark with the following configuration: GNOME Alpine Linux v3.17 x64 (i5-2520M CPU, 3.200GHz x 2 cores, 4 threads with 8GB RAM ddr4)

| Samples | Repetitions (stabilization) | Time per sample |
| ------- | --------------------------- | --------------- |
| 1000    | 10000                       | 0.000654s       |
| 10000   | 1000                        | 0.007076s       |
| 100000  | 100                         | 0.080482s       |

Those results shouldn't be taken as a reference, but they are not manipulated. The purpose of this benchmark is to see the performance of the library, allowing the user to see how it performs.

NOTE: The benchmark was made with the [benchmark.c](tests/benchmark.c) file.

## Usage

For the usage of the TableC library, you can see either in the [docs folder](docs/en-us/about.md) or in the [tests folder](tests/special_cases.c), where you can see how to use it, and how it works.

The docs folder is a way to see the usage of the library, and how each function works, and the tests folder is the code that tests TableC before committing changes to the TableC repository.

## Documentation

The documentation can be seen in the [docs folder](docs/en-us/about.md), with handwrote documentation specific to each function, with detailed and complete explanations of all (public) functions.

## Why TableC?

One of the best reasons to use TableC is because of its high portability, allowing it to be compiled on any system, and because of its high performance, which allows it to be used on low-end machines.

Other reasons are its simplicity, completeness, low-level API, and its performance.

## Contributing

Contributions are always welcome, and we are always open to new ideas, and new ways to improve the library. (not limited to the source code)

There are some guidelines that you should follow before contributing, and they are in the [contributing file](CONTRIBUTING.md). They are required to contribute to the project.

## Support

TableC is a PerformanC software, and because of that, any type of question can be asked on PerformanC's [Discord server](https://discord.gg/uPveNfTuCJ). Feel free to join our Discord to talk with us.

## License

TableC is licensed under PerformanC's License, which is a modified version of the MIT License, focusing on the protection of the source code and the rights of the PerformanC team over the source code.

If you wish to use some part of the source code, you must contact us first, and if we agree, you can use the source code, but you must give us credit for the source code you use.

## Projects using TableC

Since TableC is a new library, it is not a popular library, and it is not used in many projects, but in case you have an Open Source project using TableC, feel free to make a pull request adding it to this list.

[Coglink](https://github.com/PerformanC/Coglink) by PerformanC (TableC team)

- Feito com :heart: por um Brasileiro!
