/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:46:08 by jsarabia          #+#    #+#             */
/*   Updated: 2023/09/11 14:46:53 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_pick(t_philo *philo, t_universe *u)
{
	int				time;

	take_first_fork(philo, u);
	time = get_time(u);
	message(u, philo, FORK, time);
	take_second_fork(philo, u);
	time = get_time(u);
	message(u, philo, FORK, time);
	message(u, philo, EAT, time);
	philo->last_bite = time;
	philo->bites++;
	return (0);
}

int	ft_drop(t_philo *philo, t_universe *universe)
{
	pthread_mutex_unlock(&universe->forks[philo->l_fork]);
	pthread_mutex_unlock(&universe->forks[philo->r_fork]);
	return (0);
}

int	ft_eat(t_philo *philo, t_universe *universe)
{
	ft_pick(philo, universe);
	pthread_mutex_lock(&philo->action);
	ft_usleep(universe->time_to_eat, universe);
	pthread_mutex_unlock(&philo->action);
	ft_drop(philo, universe);
	if (ask_death(universe))
		return (1);
	return (0);
}

int	ft_sleep(t_philo *philo, t_universe *universe)
{
	int				time;
	struct timeval	t;

	gettimeofday(&t, NULL);
	time = ((t.tv_sec * 1000) + (t.tv_usec / 1000)) - universe->start;
	message(universe, philo, SLEEP, time);
	pthread_mutex_lock(&philo->action);
	ft_usleep(universe->time_to_sleep, universe);
	pthread_mutex_unlock(&philo->action);
	if (ask_death(universe))
		return (1);
	return (0);
}

int	ft_think(t_philo *philo, t_universe *universe)
{
	int				time;
	struct timeval	t;

	gettimeofday(&t, NULL);
	time = ((t.tv_sec * 1000) + (t.tv_usec / 1000)) - universe->start;
	if (ask_death(universe))
		return (1);
	message(universe, philo, THINK, time);
	pthread_mutex_lock(&philo->action);
	usleep(500);
	pthread_mutex_unlock(&philo->action);
	if (ask_death(universe))
		return (1);
	return (0);
}
