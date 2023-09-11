/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taking_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:43:22 by jsarabia          #+#    #+#             */
/*   Updated: 2023/09/11 14:49:01 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_first_fork(t_philo *philo, t_universe *u)
{
	if (philo->pos % 2 != 0 && u->forks_status[philo->l_fork] == FREE)
	{
		pthread_mutex_lock(&u->forks[philo->l_fork]);
		u->forks_status[philo->l_fork] = TAKEN;
	}
	else if (philo->pos % 2 == 0 && u->forks_status[philo->r_fork] == FREE)
	{
		pthread_mutex_lock(&u->forks[philo->r_fork]);
		u->forks_status[philo->r_fork] = TAKEN;
	}
}

void	take_second_fork(t_philo *philo, t_universe *u)
{
	if (philo->pos % 2 != 0 && u->forks_status[philo->r_fork] == FREE)
	{
		pthread_mutex_lock(&u->forks[philo->r_fork]);
		u->forks_status[philo->r_fork] = TAKEN;
	}
	else if (philo->pos % 2 == 0 && u->forks_status[philo->l_fork] == FREE)
	{
		pthread_mutex_lock(&u->forks[philo->l_fork]);
		u->forks_status[philo->l_fork] = TAKEN;
	}
}