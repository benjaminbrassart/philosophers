/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 09:32:01 by bbrassar          #+#    #+#             */
/*   Updated: 2021/12/25 09:07:02 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

void	*routine_philo(void *p)
{
	t_philo *const	philo = p;

	pthread_mutex_lock(&philo->sim->start_lock);
	pthread_mutex_unlock(&philo->sim->start_lock);
	while (1)
	{
		if (!is_running(philo->sim) || !is_alive(philo))
			break ;
		pthread_mutex_lock(philo->fork1);
		philo_log(philo, ACTION_FORK);
		pthread_mutex_lock(philo->fork2);
		philo_log(philo, ACTION_FORK);
		set_eating(philo, 1);
		philo_log(philo, ACTION_EAT);
		usleep(philo->sim->time_eat * 1000);
		set_last_eat(philo, now());
		set_eating(philo, 0);
		pthread_mutex_unlock(philo->fork1);
		pthread_mutex_unlock(philo->fork2);
		philo_log(philo, ACTION_SLEEP);
		usleep(philo->sim->time_sleep * 1000);
		philo_log(philo, ACTION_THINK);
	}
	return (NULL);
}

void	*routine_monitor(void *s)
{
	t_sim *const		sim = s;
	unsigned long long	last_eat;
	unsigned int		n;

	pthread_mutex_lock(&sim->start_lock);
	pthread_mutex_unlock(&sim->start_lock);
	while (is_running(sim))
	{
		n = 0;
		while (n < sim->philo_count)
		{
			if (!is_eating(&sim->philos[n]))
			{
				last_eat = get_last_eat(&sim->philos[n]);
				if (now() > last_eat + sim->time_die)
				{
					philo_log(&sim->philos[n], ACTION_DEAD);
					set_running(sim, 0);
					return (NULL);
				}
			}
			++n;
		}
		usleep(100);
	}
	return (NULL);
}
