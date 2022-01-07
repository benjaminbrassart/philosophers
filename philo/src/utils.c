/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 07:14:29 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/07 03:54:38 by bbrassar         ###   ########.fr       */
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
	t_sim *const	sim = philo->sim;

	if (!is_running(sim))
		return ;
	pthread_mutex_lock(&sim->talk_lock);
	printf(" %-6llu %u %s\n", now() - sim->start_time, philo->id + 1, action);
	pthread_mutex_unlock(&sim->talk_lock);
}
