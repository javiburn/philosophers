/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:06:23 by jsarabia          #+#    #+#             */
/*   Updated: 2023/09/11 14:33:54 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message(t_universe *uni, t_philo *philo, enum e_message flag, int t)
{
	if (ask_death(uni))
		return ;
	pthread_mutex_lock(&uni->message);
	if (flag == FORK)
		printf("%d ms	Philo %d has taken a fork\n", t, philo->pos);
	else if (flag == EAT)
		printf("%d ms	Philo %d starts eating\n", t, philo->pos);
	else if (flag == SLEEP)
		printf("%d ms	Philo %d starts sleeping\n", t, philo->pos);
	else if (flag == THINK)
		printf("%d ms	Philo %d starts thinking\n", t, philo->pos);
	else if (flag == DIE)
		printf("%d ms	Philo %d has died\n", t, philo->pos);
	pthread_mutex_unlock(&uni->message);
}

void	ft_usleep(int ms, t_universe *universe)
{
	int				time;
	int				start;
	struct timeval	t;

	gettimeofday(&t, NULL);
	start = ((t.tv_sec * 1000) + (t.tv_usec / 1000)) - universe->start;
	ms = ms + start;
	time = 0;
	while (time < ms)
	{
		usleep(500);
		gettimeofday(&t, NULL);
		time = ((t.tv_sec * 1000) + (t.tv_usec / 1000)) - universe->start;
	}
}
