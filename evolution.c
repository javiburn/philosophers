/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evolution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:06:12 by jsarabia          #+#    #+#             */
/*   Updated: 2023/09/08 16:43:48 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*will(void *arg)
{
	t_universe	*universe;
	t_philo		*philo;

	philo = (t_philo *)arg;
	universe = philo->universe;
	philo->bites = 0;
	if (philo->pos % 2 == 0)
	{
		pthread_mutex_lock(&philo->action);
		usleep(30000);
		pthread_mutex_unlock(&philo->action);
	}
	while (!ask_death(universe))
	{
		if (ft_eat(philo, universe))
			break ;
		if (ft_sleep(philo, universe))
			break ;
		if (ft_think(philo, universe))
			break ;
	}
	return (NULL);
}

static int	*create_array(int *checker, t_universe *universe)
{
	int	aux;

	aux = 0;
	checker = malloc(universe->num_philos * sizeof(int));
	while (aux < universe->num_philos)
	{
		checker[aux] = 0;
		aux++;
	}
	return (checker);
}

void	*cycle_of_life(int i, t_universe *u, int *c)
{
	pthread_mutex_lock(&u->freemutex);
	while (1)
	{
		usleep(500);
		while (i < u->num_philos)
		{
			if (check_death(u, u->philo[i]))
				return (free(c), pthread_mutex_unlock(&u->freemutex), NULL);
			if (u->eat_reps > 0)
			{
				if (check_bites(u, u->philo[i], &c))
					return (free(c), pthread_mutex_unlock(&u->freemutex), NULL);
			}
			i++;
		}
		i = 0;
	}
	return (free(c), pthread_mutex_unlock(&u->freemutex), NULL);
}

void	*go_to_hell(void *arg)
{
	t_universe	*u;
	t_philo		*philo;
	int			i;
	int			*c;

	i = 0;
	c = NULL;
	philo = (t_philo *)arg;
	u = (t_universe *)philo->universe;
	c = create_array(c, u);
	if (u->eat_reps < 0)
	{
		pthread_mutex_lock(&u->freemutex);
		ft_usleep(u->time_to_die - 1, u);
		pthread_mutex_unlock(&u->freemutex);
	}
	cycle_of_life(i, u, c);
	return (NULL);
}

int	evolving(t_universe *universe)
{
	int			i;

	i = 0;
	universe = set_philos_universe(universe);
	pthread_create(&universe->hell, NULL,
		&go_to_hell, &universe->philo[0]);
	pthread_detach(universe->hell);
	while (i < universe->num_philos)
	{
		if (pthread_create(&universe->philo[i].philos, NULL,
				&will, &universe->philo[i]))
			return (1);
		i++;
	}
	i = 0;
	while (i < universe->num_philos)
	{
		if (pthread_join(universe->philo[i].philos, NULL))
			return (2);
		i++;
	}
	return (0);
}
