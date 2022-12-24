# TableC

Advanced and portable closed-addressing hashtable implementation for C.

## Features

- [x] Simple & low-level API
- [x] Expandable hashtable
- [x] Set keys and values
- [x] Get values based on the key
- [x] Remove keys and values

## Performance

TableC has high efficiency and performance, allowing it to be used on embedded systems, as well as on high-end devices like servers and desktops.

It has an incredible speed, especially when in good conditions for it, such as deleting a key after using it.

And all that for a new library, that was not fully optimized yet, but it's getting there.

We made a benchmark using one of our benchmarking codes, and the results are:

GNOME Alpine Linux v3.17 x64 (i5-2520M CPU, 3.200GHz x 2 cores, 4 threads with 8GB RAM ddr4)

| Samples | Repetitions (stabilization) | Time per sample |
| ------- | --------------------------- | --------------- |
| 1000    | 10000                       | 0.008209s       |
| 10000   | 1000                        | 0.000755s       |
| 100000  | 100                         | 0.093375s       |

Those results shouldn't be taken as a reference, but they are not manipulated. The purpose of this benchmark is to see the performance of the library, allowing the user to see how it performs.

## Usage

For the usage of the TableC library, you can see either in the [docs folder](docs/en-us/about.md), or in the [tests folder](tests/special_cases.c), where you can see how to use it, and how it works.

The docs folder is a way to see the usage of the library, and how each function works, and the tests folder is the code that tests TableC before committing changes to the TableC repository.

## Documentation

The documentation can be seen in the [docs folder], with handwriting documentation specific to each function, with detailed and complete explanations of all (public) functions.

## Why TableC?

One of the best reasons to use TableC is because of its high portability, allowing it to be compiled on any system, and because of its high performance, which allows it to be used on low-end and embedded systems.

Another reason is that it is simple, complete, and has good documentation.

## Contributing

Contributions are always welcome, and we are always open to new ideas, and new ways to improve the library, although not limited to the TableC files, but also the documentation.

There are some guidelines that you should follow before contributing, and they are in the [contributing file](CONTRIBUTING.md), and if you follow them, you will be able to contribute to the TableC project.

## Support

TableC is a PerformanC project, and because of that, any type of question can be asked on PerformanC's [Discord server](https://discord.gg/uPveNfTuCJ), and feel free to join our Discord to talk with us.

## License

TableC uses a customized license created by PerformanC, which has the same rights as a MIT license, except it includes a clause stating that you cannot use this software (library) to train a neural network.

## Projects using TableC

Since TableC is a new library, it is not a popular library, and it is not used in many projects, but in case you have an Open Source project using TableC, feel free to make a pull request adding it to this list.

[Experimental] [Coglink](https://github.com/PerformanC/Coglink) by PerformanC (TableC team)

* Feito com :heart: por um Brasileiro! 🇧🇷