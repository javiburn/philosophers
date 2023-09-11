/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taking_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:43:22 by jsarabia          #+#    #+#             */
/*   Updated: 2023/09/11 15:39:46 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_first_fork(t_philo *philo, t_universe *u)
{
	if (philo->pos % 2 != 0)
	{
		pthread_mutex_lock(&u->forks[philo->l_fork]);
		if (u->forks_status[philo->l_fork] == FREE)
			u->forks_status[philo->l_fork] = TAKEN;
	}
	else
	{
		pthread_mutex_lock(&u->forks[philo->r_fork]);
		if (u->forks_status[philo->r_fork] == FREE)
			u->forks_status[philo->r_fork] = TAKEN;
	}
}

void	take_second_fork(t_philo *philo, t_universe *u)
{
	if (philo->pos % 2 != 0)
	{
		pthread_mutex_lock(&u->forks[philo->r_fork]);
		if (u->forks_status[philo->r_fork] == FREE)
			u->forks_status[philo->r_fork] = TAKEN;
	}
	else
	{
		pthread_mutex_lock(&u->forks[philo->l_fork]);
		if (u->forks_status[philo->l_fork] == FREE)
			u->forks_status[philo->l_fork] = TAKEN;
	}
}
