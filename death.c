/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 16:55:11 by jsarabia          #+#    #+#             */
/*   Updated: 2023/09/07 19:16:25 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_universe *universe, t_philo philo)
{
	int				time;
	struct timeval	t;

	pthread_mutex_lock(&universe->mutex);
	gettimeofday(&t, NULL);
	time = ((t.tv_sec * 1000) + (t.tv_usec / 1000)) - universe->start;
	if (time - philo.last_bite > universe->time_to_die)
	{
		universe->death = 1;
		if (philo.bites != universe->eat_reps)
		{
			pthread_mutex_lock(&universe->message);
			printf("%d ms	Philo %d has died\n", time, philo.pos);
			pthread_mutex_unlock(&universe->message);
		}
		pthread_mutex_unlock(&universe->mutex);
		return (time);
	}
	pthread_mutex_unlock(&universe->mutex);
	return (0);
}

int	check_bites(t_universe *universe, t_philo philo, int **checker)
{
	static int	num = 0;

	if (philo.bites == universe->eat_reps)
	{
		if ((*checker)[philo.pos - 1] == 0)
		{
			(*checker)[philo.pos - 1] = 1;
			num++;
		}
		if (num == universe->num_philos)
			return (1);
	}
	return (0);
}

void	destroy_mutexes(t_universe *universe)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&universe->mutex);
	pthread_mutex_destroy(&universe->freemutex);
	pthread_mutex_destroy(&universe->message);
	while (i < universe->num_philos)
	{
		pthread_mutex_destroy(&universe->forks[i]);
		pthread_mutex_destroy(&universe->philo[i].action);
		i++;
	}
}

int	ask_death(t_universe *universe)
{
	pthread_mutex_lock(&universe->mutex);
	if (universe->death == 0)
	{
		pthread_mutex_unlock(&universe->mutex);
		return (0);
	}
	pthread_mutex_unlock(&universe->mutex);
	return (1);
}
