/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 07:14:29 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/03 04:23:40 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stddef.h>
#include <stdio.h>
#include <sys/time.h>

unsigned long long	now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	philo_log(t_philo *philo, char const *action)
{
	if (!is_running(philo->sim))
		return ;
	pthread_mutex_lock(&philo->sim->talk_lock);
	printf("%llu %u %s\n", now(), philo->id + 1, action);
	pthread_mutex_unlock(&philo->sim->talk_lock);
}
