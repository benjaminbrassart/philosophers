/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 09:32:01 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/17 17:37:53 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static int	check_eat_count(t_philo *philo)
{
	if (philo->sim->has_goal && increase_eat_count(philo) >= philo->sim->goal)
	{
		set_alive(philo, 0);
		return (1);
	}
	return (0);
}

void	*routine_philo(void *p)
{
	t_philo *const	philo = p;

	pthread_mutex_lock(&philo->sim->start_lock);
	pthread_mutex_unlock(&philo->sim->start_lock);
	while (is_running(philo->sim) && is_alive(philo))
	{
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
		if (check_eat_count(philo))
			break ;
		philo_log(philo, ACTION_SLEEP);
		usleep(philo->sim->time_sleep * 1000);
		philo_log(philo, ACTION_THINK);
	}
	set_alive(philo, 0);
	return (NULL);
}

static int	routine_monitor_philo(t_philo *philo)
{
	unsigned long long	last_eat;

	if (is_alive(philo) && !is_eating(philo))
	{
		last_eat = get_last_eat(philo);
		if (now() > last_eat + philo->sim->time_die * 1000)
		{
			philo_log(philo, ACTION_DEAD);
			set_running(philo->sim, 0);
			return (1);
		}
	}
	return (0);
}

void	*routine_monitor(void *s)
{
	t_sim *const	sim = s;
	unsigned int	n;

	pthread_mutex_lock(&sim->start_lock);
	pthread_mutex_unlock(&sim->start_lock);
	while (is_running(sim) && get_alive_count(sim) > 0)
	{
		n = 0;
		while (n < sim->philo_count)
			if (routine_monitor_philo(&sim->philos[n++]))
				return (NULL);
		usleep(100);
	}
	return (NULL);
}
