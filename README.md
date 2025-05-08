# Philosophers

## Table of Contents
1. [Description](#description)
2. [Installation](#installation)
3. [Run](#run)
4. [Credits](#credits)
5. [Contributing](#contributing)
6. [License](#license)

## Description

Philosophers is a project from the 42 Common Core curriculum. The purpose of this project is to explore multithreading programming by illustrating the famous Dining Philosophers problem. The project focuses on the creation and management of threads and mutexes to control access to shared resources.

### Purpose

The purpose of this program is to simulate the dining philosophers problem by displaying each philosopher's actions: eating, sleeping, or thinking. This is essentially a way to "illustrate" how threads function in a multithreaded environment.

### Technologies used

- C language.
- Make.

### Challenges and Future Features

The main challenges were learning how threads are created, understanding the purpose of mutexes, preventing data races, and building an efficient algorithm to keep the philosophers alive as long as possible.

I'm not planning to add new features.

## Installation

- Ensure you have a C compiler installed, such as [Clang](https://clang.llvm.org/) or [GCC](https://gcc.gnu.org/)
```bash
clang --version
gcc --version
```
- Ensure you have installed [Make](https://www.gnu.org/software/make/) to build the project
```bash
make --version
```

## Run

1. Build the project:
```bash
make
```

2. This will create a `./philo` binary.

3. Run the program with the following arguments:

```bash
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [meal_count (optional)]
```

`number_of_philosophers`: Number of philosophers (and forks).

`time_to_die`: Time in milliseconds before a philosopher dies if they don't start eating.

`time_to_eat`: Time in milliseconds it takes for a philosopher to eat.

`time_to_sleep`: Time in milliseconds a philosopher spends sleeping.

`meal_count` (optional): Number of times each philosopher must eat. If all philosophers eat this amount, the simulation ends.

## Credits

Thanks to [CodeVault](https://www.youtube.com/@CodeVault) and [Uilly93](https://github.com/Uilly93) for the basics of multithreading.

A special thanks to [Blaxx23](https://github.com/Blaxx23) who pointed out that my "lock order not consistent" error was only occurring with the first philosopher and explained the solution.

## Contributing

To report issues, please create an issue here:  [issue tracker](https://github.com/Vpekdas/philosophers/issues).

If you'd like to contribute, please follow the steps outlined in [CONTRIBUTING.md](CONTRIBUTING.md).

## License

This project is licensed under the [MIT License](LICENSE).
