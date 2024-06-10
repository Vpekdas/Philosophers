# Philosophers

# Table of Contents
1. [Description](#description)
2. [Installation Instructions](#installation-instructions)
3. [Usage Instructions](#usage-instructions)
4. [Key Features](#key-features)
5. [Contribution Guidelines](#contribution-guidelines)
6. [Acknowledgments](#acknowledgments)
7. [License Information](#license-information)
8. [Contact Information](#contact-information)
9. [Project Development](#project-development)

## Description

This project, "Philosophers", is an implementation of the classic concurrency problem known as the Dining Philosophers problem. It's written in C and uses multithreading and mutex functions to simulate the actions of philosophers as they alternate between eating and thinking. The goal of the project is to avoid deadlock and ensure fairness, so that each philosopher gets a fair chance to eat and think. This project serves as a practical exercise in understanding and applying the concepts of multithreading and synchronization.

## Installation Instructions

Before you begin, ensure you have met the following requirements:

1. **Download the project**: You can clone the project from GitHub using the following command in your terminal:
```bash
git clone https://github.com/Vpekdas/Philosophers.git
```

2. **Install a C compiler**: If you don't already have a C compiler installed, you will need one to build and use this library. You can install the [Clang compiler](https://clang.llvm.org).
   
- On a Mac, you should already have Clang installed as part of Xcode Command Line Tools. You can confirm this by running clang --version in your terminal. If it's not installed, you'll be prompted to install it.

- On a Linux machine, use the package manager for your distribution. For example, on Ubuntu:
```bash
sudo apt install clang
```

## Usage Instructions

Follow these steps to use the Philosophers project:

1. **Compile the Project:** Navigate to the cloned repository and compile the project using the provided Makefile. Execute the following command in your terminal:
```bash
make
```
This command will create an executable named `philo`.

2. **Run the Program:** The `philo`program accepts 4 or 5 arguments: 

   - Number of philosophers (limited to 200)
   - Time to die
   - Time to eat
   - Time to think
   - Optional: Meal count (if this argument is provided, it specifies the number of meals)

   For example, to run the program with 5 philosophers, each with 800ms to die, 200ms to eat, and 200ms to think, use the following command:
```bash
./philo 5 800 200 200
```

3. **Specify a Meal Count:** If you want to end the simulation after a certain number of meals, provide a fifth argument for the meal count. For example, to end the simulation after 7 meals, use the following command:
```bash
./philo 5 800 200 200 7
```

## Key Features

### Understanding dining philospoher problem:
The first thing I did was to research more about this problem. I came across many solutions using different approaches (such as Dijkstra's solution and the Resource Hierarchy solution). These seemed a bit complicated, but I was advised by many students that it wasn't necessary to code such a sophisticated approach for this project.

### Understanding how thread and mutex function works:
As usual, I turned to [CodeVault](https://www.youtube.com/@CodeVault) for guidance. The explanations provided on how threads work, what a data race is, and how to avoid them were very clear! I also want to thank [Uilly93](https://github.com/Uilly93) for explaining his approach to me, which saved me a lot of time (especially after receiving a zero score in three peer-to-peer corrections).

### Choosing a structure:
I decided to create a structure because I knew I would need to store a lot of information. Here's an example of the structure that I used:

Global variables are forbidden, so I'm passing a pointer to my program to each philosopher. This isn't intended to allow the philosophers to communicate, but rather to allow the program to monitor and check if a philosopher has died or if they have eaten enough.
```C
typedef struct s_philo
{
	pthread_t		thread;
	size_t			philo_id;
	size_t			philo_nb;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			nb_to_eat;
	size_t			meal_eaten;
	size_t			last_meal_time;
	size_t			start_time;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_program		*program;
}		t_philo;

typedef struct s_program
{
	size_t			is_philo_dead;
	size_t			start;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	*forks;
	t_philo			**philos;
}					t_program;
```

### Adding fairness:
During my initial attempts to validate this project, I was surprised to find that my implementation was inconsistent. Sometimes, a philosopher would starve when they shouldn't have. This led me to realize that I needed to introduce some fairness into the threading. My initial approach was to give no specific order, allowing the first philosopher to grab the forks to eat. It worked on my PC, so I didn't initially see the issue! However, after these failures, I've made a commitment to thoroughly test each scenario at least 30 times to ensure its reliability. In the following sections, I will delve deeper into the fairness mechanisms I've implemented.

### Valgrind's `--fair-sched=try` Option
Valgrind's --fair-sched=try option is a setting that tries to make sure all threads in your program get an equal chance to run. This can help find problems in your code that only show up when threads run in a certain order. However, it can't always guarantee perfect fairness due to the way your program works. If you see errors when using this option, it could mean there's a hidden issue in your code that might cause problems later. Giving equal run to threads means that each thread in your program gets an equal opportunity to execute.

---

* The problem begins with the fact that a philosopher needs two forks to eat. However, each philosopher starts with only one, which means they need to borrow a fork. I'm solving this problem by creating an array of forks and assigning the index of this array to the right fork. For example, philosopher 1 will take `forks[0]` and philosopher 2 will take `forks[1]`, and so on.
* For the left forks, I'm simulating a circular table by calculating `fork[(i + philo_nb - 1) % philo_nb]`. For instance, with 5 philosophers: philosopher 1's left fork will be `(0 + 5 - 1) % 5 = 4`. The 4th index is the right fork of the last philosopher. Philosopher 2's left fork will be `(1 + 5 - 1) % 5 = 0`. The 0th index is the right fork of the first philosopher.
* The last step is to lock these forks to signal to other philosophers that I've taken their forks. The challenge here is to avoid the error "inconsistent lock order" given by `valgrind --tool=helgrind`. For more precision, you can add the flag `--fair-sched=try`. The idea is to lock the fork with the lower ID first, then lock the fork with a greater ID. Basically, I lock my left forks then the right ones. There is a small exception for the first philosopher. The left fork of philosopher 1 is the last, so it's greater, so I'm adjusting that so the lock order is always consistent. The order in which the locks are released is not important.

```C
static void	assign_forks(t_philo **philos, size_t philo_nb, t_program *program)
{
	size_t	i;

	i = 0;
	while (i < philo_nb)
	{
		philos[i]->r_fork = &program->forks[i];
		philos[i]->l_fork = &program->forks[(i + philo_nb - 1) % philo_nb];
		++i;
	}
}

static void	lock_unlock_fork(enum e_fork fork, t_philo *philo)
{
	if (fork == LOCK)
	{
		if (philo->philo_id == 1)
		{
			pthread_mutex_lock(philo->r_fork);
			print_message(TAKEN_A_FORK, philo);
			pthread_mutex_lock(philo->l_fork);
			print_message(TAKEN_A_FORK, philo);
		}
		else
		{
			pthread_mutex_lock(philo->l_fork);
			print_message(TAKEN_A_FORK, philo);
			pthread_mutex_lock(philo->r_fork);
			print_message(TAKEN_A_FORK, philo);
		}
	}
	else if (fork == UNLOCK)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
}
```
---
Now, let's talk about fairness:
* The first thing I've added is to make the even-numbered philosophers wait so the odd-numbered ones can start first. This will establish a sort of rhythm.

* The next thing I'm doing is to introduce a 1 ms sleep after a philosopher has slept. Why did I do that? Because I noticed that sometimes the same philosopher could eat twice in a row without giving his forks to his neighbor, and then one was starving. This small delay does not impact the tests (even the toughest ones) and gives the chance for other philosophers to eat.
```C
void	*routine(t_philo *philo)
{
	if (philo->philo_nb == 1)
		return (one_philo(philo));
	if (philo->philo_id % 2 == 0)
		ft_usleep(philo->time_to_eat / 2, philo->program, philo);
	while (1)
	{
		pthread_mutex_lock(&philo->program->death_lock);
		if (philo->program->is_philo_dead != 0
			|| philo->meal_eaten >= philo->nb_to_eat)
		{
			pthread_mutex_unlock(&philo->program->death_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->program->death_lock);
		eat_and_sleep(philo);
		ft_usleep(1, philo->program, philo);
		print_message(THINKING, philo);
	}
	return (NULL);
}
```

Finally, my main function looks like this:
* I'm always checking if one step fails and then return an error and free the resources.
* I've decided to discuss only the parts that I've spent the most time on. Feel free to check each .c file in detail if needed.
```C
int	main(int ac, char **av)
{
	t_philo		**philos;
	t_program	program;

	philos = NULL;
	program = (t_program){0};
	if (ac == 5 || ac == 6)
	{
		if (overall_parsing_check(ac, av) == ERROR)
			return (free_struct(philos, &program, ERROR));
		philos = init_philo_struct(av, &program);
		if (!philos)
			return (free_struct(philos, &program, ERROR_CALLOC));
		fill_parsing(ac, av, philos, &program);
		if (create_forks(philos[0]->philo_nb, &program) == ERROR_INIT_MUTEX)
			return (free_struct(philos, &program, ERROR_INIT_MUTEX));
		if (create_thread(philos, routine) == ERROR_INIT_THREAD)
			return (free_struct(philos, &program, ERROR_INIT_THREAD));
		end_loop(philos, &program);
		join_thread(philos, philos[0]->philo_nb);
		free_struct(philos, &program, OK);
	}
	else
		argc_error(ac);
}
```
## Acknowledgments

Once again, thanks to [CodeVault](https://www.youtube.com/@CodeVault) and [Uilly93](https://github.com/Uilly93) for the basics of multithreading.

A special thanks to [Blaxx23](https://github.com/Blaxx23) who pointed out that my "lock order not consistent" error was only occurring with the first philosopher and explained the solution.

## Contribution Guidelines

I welcome contributions from everyone. Here are some guidelines to follow:

1. **Fork the repository**: Start by forking the repository to your own GitHub account.

2. **Clone the repository**: Clone the forked repository to your local machine.
```bash
git clone https://github.com/Vpekdas/Philosophers.git
```

3. **Create a new branch**: Create a new branch for each feature or bug fix you're working on. Do not make changes directly on the master branch
```bash
git checkout -b your-branch-name
```

4. **Make your changes**: Make your changes in the new branch. Ensure your code follows the [norminette](https://github.com/42School/norminette).

5. **Commit your changes**: Commit your changes regularly with clear, descriptive commit messages.
```bash
git commit -m "Your commit message"
```

6. **Push your changes**: Push your changes to your forked repository on GitHub.
```bash
git push origin your-branch-name
```

7. **Create a pull request**: Go to your forked repository on GitHub and create a new pull request against the master branch.
Please note that this project has a code of conduct, and contributors are expected to adhere to it. Any contributions you make are greatly appreciated.

## License Information

This project is licensed under the [MIT License](LICENSE).

The MIT License is a permissive license that is short and to the point. It lets people do anything they want with your code as long as they provide attribution back to you and don’t hold you liable.

For the full license text, see the [LICENSE](LICENSE) file.

## Contact Information

If you have any questions, issues, or if you want to contribute, feel free to reach out to me:

- GitHub: [@Vpekdas](https://github.com/Vpekdas)
- Discord: Captain-Plouf#7811

## Project Development

### Development Process

The development of the "Philosophers" project began with understanding the problem and the concept of multithreading. I then researched extensively on multithreading and mutex functions.

### Challenges and Solutions

The main challenge was ensuring fairness in threading and avoiding deadlock. After several iterations and testing, I was able to implement a solution that ensures each philosopher gets a fair chance to eat and think, thereby avoiding deadlock.

### Tools and Technologies Used

The "Philosophers" project was developed using C.

### Lessons Learned

The development of "Philosophers" taught me the intricacies of multithreading and mutex functions. It also taught me the importance of fairness in threading and how to avoid deadlock.

### Future Plans

There are currently no plans to further improve the "Philosophers" project. The experience gained from this project has been invaluable and will be applied to future projects.

### Current Status

The project is currently complete and not in active development. However, maintenance and updates will be done as needed.

### Future Plans

Plans for future development include adding more functions, improving performance, and expanding the documentation.

### Known Issues

There are currently no known issues. If you find a bug, please report it in the [issue tracker](https://github.com/Vpekdas/philosophers/issues).

### Contributing

Contributions are always welcome! See the [Contribution Guidelines](#contribution-guidelines) for more information.
