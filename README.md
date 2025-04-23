# Philosophers

This project simulates the classic Dining Philosophers Problem, a fundamental exercise in concurrent programming. It is designed to deepen understanding of threads, mutexes, and the importance of avoiding race conditions and deadlocks in a multithreaded environment.

<div align="center">
	<img src="resources/philo.jpg" alt="Philo" width="80%">
</div>

In the simulation, a number of philosophers sit around a table. Between each pair of philosophers lies a single fork. A philosopher can only eat if they have both the left and right fork. Philosophers spend their lives alternately thinking, eating, and sleeping—but if a philosopher cannot acquire both forks, they must wait, potentially indefinitely. This creates potential for synchronization issues, which the program must resolve efficiently. The challenge lies in managing access to these shared resources without causing deadlock, starvation, or other concurrency bugs.


## Getting Started

1. Clone the repository:

   ```bash
   git clone https://github.com/jesuismarie/Philosophers.git
   ```

2. Change into the project directory:

   ```bash
   cd Philosophers
   cd philo
   ```
   or
   ```bash
   cd Philosophers
   cd philo_bonus
   ```

3. Compile the program:

   ```bash
   make
   ```

4. Run Philosophers:

   ```bash
   ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
   ```

- `number_of_philosophers`: total number of philosophers and forks.
- `time_to_die`: time (ms) until a philosopher dies without eating.
- `time_to_eat`: time (ms) it takes a philosopher to eat.
- `time_to_sleep`: time (ms) a philosopher will sleep after eating.
- `[number_of_times_each_philosopher_must_eat]`: *(optional)* stop simulation when all philosophers have eaten this many times.