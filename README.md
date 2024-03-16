# TableC

Low-level C89 closed and open addressing hashtable library.

## Features

- [x] Expandable hashtable
- [x] Overflow protected
- [x] No memory leaks
- [x] C89 compatible
- [x] [Extremely customizable](https://github.com/PerformanC/TableC/tree/open-addressing-customizable)


## Performance

TableC, due to its low-level API, and its simplicity, has a high performance, allowing it to be used on machines with restricted resources.

| Samples | Repetitions (stabilization) | Time per sample |
| ------- | --------------------------- | --------------- |
| 1000    | 10000                       | 0.000718s       |
| 10000   | 1000                        | 0.008083s       |
| 100000  | 100                         | 0.095981s       |

> [!NOTE]
> This benchmark is only a reference, and must not be considered as a definitive result. If you want to run the benchmark yourself, you can do it by running the [benchmark.c](tests/benchmark.c) file.

## Usage

TableC provides an easy to use API, and a lot of flavors.

- Closed addressing (main)
- [Open addressing](https://github.com/PerformanC/TableC/tree/open-addressing)
- [Open addressing without dynamic allocation](https://github.com/PerformanC/TableC/tree/open-addressing-no-malloc)
- [Open addressing highly customizable](https://github.com/PerformanC/TableC/tree/open-addressing-customizable)

Each flavor has its own advantages and disadvantages, and you can choose the one that best suits your needs. You can see its usage in the [tests folder](tests/special_cases.c) and in the [docs folder](docs/en-us/about.md).

## Documentation

The docs provides a hand-written documentation for each function, with detailed explanations of each function, and its parameters. They are available in both English and Portuguese, and you can see it in the [docs folder](docs/).

## Support

TableC is a PerformanC software, and because of that, any type of question can be asked on PerformanC's [Discord server](https://discord.gg/uPveNfTuCJ). Feel free to join our Discord to talk with us.

## Contributing

TableC follows the organization's [contribution guidelines](https://github.com/PerformanC/contributing). You can read it to know how to contribute to TableC and other PerformanC projects.

## Projects using TableC

Since TableC is a new library, it is not a popular library, and it is not used in many projects, but in case you have an Open Source project using TableC, feel free to make a pull request adding it to this list.

[Coglink](https://github.com/PerformanC/Coglink) by PerformanC
[Cog-chef][https://github.com/Cogmasters/cog-chef] by Cogmasters

## License

TableC is licensed under [BSD 2-Clause License](LICENSE). You can read more about it on [Open Source Initiative](https://opensource.org/licenses/BSD-2-Clause).

- Feito com :heart: por um Brasileiro!
