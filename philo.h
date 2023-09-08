/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:44:49 by jsarabia          #+#    #+#             */
/*   Updated: 2023/09/07 17:32:42 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

enum e_message
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
};

typedef struct s_universe
{
	int				start;
	int				death;
	int				corpse;
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_reps;
	int				*i;
	struct s_philo	*philo;
	struct timeval	time;
	pthread_t		hell;
	pthread_mutex_t	message;
	pthread_mutex_t	freemutex;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*forks;
}	t_universe;

typedef struct s_philo
{
	int				pos;
	int				bites;
	int				l_fork;
	int				r_fork;
	int				last_bite;
	pthread_t		philos;
	t_universe		*universe;
	pthread_mutex_t	action;
}	t_philo;

int			new_atoi(const char *nptr);
int			all_digit(char *num);
void		message(t_universe *uni, t_philo *p, enum e_message flag);
int			evolving(t_universe *universe);
void		ft_usleep(int ms, t_universe *universe);
int			check_death(t_universe *universe, t_philo philo);
int			check_bites(t_universe *universe, t_philo philo, int **checker);
int			ask_death(t_universe *universe);
t_universe	*set_philos_universe(t_universe *universe);
int			ft_pick(t_philo *philo, t_universe *universe);
int			ft_drop(t_philo *philo, t_universe *universe);
int			ft_eat(t_philo *philo, t_universe *universe);
int			ft_sleep(t_philo *philo, t_universe *universe);
int			ft_think(t_philo *philo, t_universe *universe);
void		destroy_mutexes(t_universe *universe);

#endif
