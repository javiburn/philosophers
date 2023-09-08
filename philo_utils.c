/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 18:19:58 by jsarabia          #+#    #+#             */
/*   Updated: 2023/08/23 18:30:25 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	new_atoi(const char *nptr)
{
	int	n;
	int	sign;
	int	res;

	n = 0;
	sign = 1;
	res = 0;
	while (nptr[n] == ' ' || nptr[n] == '\n' || nptr[n] == '\t'
		|| nptr[n] == '\v' || nptr[n] == '\f' || nptr[n] == '\r')
		n++;
	if (nptr[n] == '-' || nptr[n] == '+')
	{
		if (nptr[n] == '-')
			sign = -1;
		n += 1;
	}
	while (nptr[n] >= '0' && nptr[n] <= '9')
	{
		res = res * 10;
		res = res + (nptr[n] - '0');
		n++;
		if (nptr[n] < '0' || nptr[n] > '9' || nptr[n] == '\0')
			return (res * sign);
	}
	return (0);
}

int	all_digit(char *num)
{
	int	n;

	n = 0;
	while (num[n])
	{
		if (!(num[n] >= '0' && num[n] <= '9'))
			return (0);
		n++;
	}
	return (1);
}
