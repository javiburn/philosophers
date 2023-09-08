/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:43:02 by jsarabia          #+#    #+#             */
/*   Updated: 2023/09/07 19:19:09 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_universe	*set_philos_universe(t_universe *universe)
{
	int			i;
	t_universe	*aux;

	i = 0;
	aux = universe;
	while (i < universe->num_philos)
	{
		(aux->philo[i]).universe = universe;
		i++;
	}
	return (aux);
}

static int	check_parsing(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("Incorrect number of arguments\n");
		return (0);
	}
	while (argv[i])
	{
		if (!new_atoi(argv[i]) || new_atoi(argv[i]) < 1 || !all_digit(argv[i]))
		{
			printf("Invalid input\n");
			return (0);
		}
		i++;
	}
	return (1);
}

static t_universe	*set_philos_pos(t_universe *universe)
{
	int	i;

	i = 0;
	universe->forks = malloc(universe->num_philos * (sizeof(pthread_mutex_t)));
	while (i < universe->num_philos)
	{
		universe->philo[i].pos = i + 1;
		universe->philo[i].last_bite = 0;
		universe->philo[i].r_fork = i;
		universe->philo[i].l_fork = i + 1;
		if (i + 1 == universe->num_philos)
			universe->philo[i].l_fork = 0;
		pthread_mutex_init(&universe->forks[i], NULL);
		pthread_mutex_init(&universe->philo[i].action, NULL);
		i++;
	}
	return (universe);
}

t_universe	*big_bang(char **argv)
{
	t_universe	*universe;

	universe = malloc(sizeof(t_universe));
	universe->num_philos = new_atoi(argv[1]);
	universe->time_to_die = new_atoi(argv[2]);
	universe->time_to_eat = new_atoi(argv[3]);
	universe->time_to_sleep = new_atoi(argv[4]);
	if (argv[5])
		universe->eat_reps = new_atoi(argv[5]);
	else
		universe->eat_reps = -1;
	universe->philo = malloc(universe->num_philos * sizeof(t_philo));
	gettimeofday(&universe->time, NULL);
	universe->start = (universe->time.tv_sec * 1000)
		+ (universe->time.tv_usec / 1000);
	universe = set_philos_pos(universe);
	pthread_mutex_init(&universe->mutex, NULL);
	return (universe);
}

int	main(int argc, char **argv)
{
	t_universe	*universe;

	if (!check_parsing(argc, argv))
		return (1);
	universe = big_bang(argv);
	pthread_mutex_init(&universe->freemutex, NULL);
	pthread_mutex_init(&universe->message, NULL);
	if (universe->num_philos == 1)
	{
		message(universe, &universe->philo[0], FORK);
		ft_usleep(universe->time_to_die, universe);
		message(universe, &universe->philo[0], DIE);
	}
	else
		evolving(universe);
	pthread_mutex_lock(&universe->freemutex);
	pthread_mutex_unlock(&universe->freemutex);
	destroy_mutexes(universe);
	free(universe->philo);
	free(universe->forks);
	free(universe->i);
	free(universe);
	return (0);
}
