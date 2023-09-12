# Philosophers 🤔

This project is designed to learn the basics of threading a process,
including how to create threads and handling mutexes.

The problem that we have to solve is the [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) using a multi-threading solution.

Each philosopher must be one thread and there will be no communication between them. Also, each fork must be protected with a mutex. Once a philosopher dies, the simulation stops.
To calculate the death of a philosopher, I created another thread which will be constantly checking wether each philosopher is dead or alive.
With the death of one philo, this thread will finish the execution of the rest of them.

If none of the philosopher dies, the simulation keeps running until we stop it or until they have eaten x times, if we have set this condition.

![Philosophers](https://upload.wikimedia.org/wikipedia/commons/7/7b/An_illustration_of_the_dining_philosophers_problem.png "Philosophers")
