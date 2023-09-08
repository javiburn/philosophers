/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:06:23 by jsarabia          #+#    #+#             */
/*   Updated: 2023/09/07 19:18:11 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message(t_universe *uni, t_philo *philo, enum e_message flag)
{
	int				t;
	struct timeval	time;

	if (ask_death(uni))
		return ;
	pthread_mutex_lock(&uni->message);
	gettimeofday(&time, NULL);
	t = (time.tv_sec * 1000) + (time.tv_usec / 1000) - uni->start;
	if (uni->death != 0)
	{
		pthread_mutex_unlock(&uni->message);
		return ;
	}
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
		gettimeofday(&t, NULL);
		time = ((t.tv_sec * 1000) + (t.tv_usec / 1000)) - universe->start;
	}
}
