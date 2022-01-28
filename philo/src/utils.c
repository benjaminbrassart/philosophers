/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 07:14:29 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/28 05:03:13 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stddef.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

unsigned long long	now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(unsigned long long time_ms)
{
	unsigned long long const	start_time = now();

	while ((now() - start_time) < time_ms)
		usleep(time_ms / 10);
}

void	philo_log(t_philo *philo, char const *action)
{
	t_sim *const	sim = philo->sim;

	if (!is_running(sim))
		return ;
	pthread_mutex_lock(&sim->write_mutex);
	printf(" %-6llu %u %s\n", now() - sim->start_time, philo->id + 1, action);
	pthread_mutex_unlock(&sim->write_mutex);
}
