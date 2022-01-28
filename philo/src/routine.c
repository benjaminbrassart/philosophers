/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 09:32:01 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/28 07:37:25 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static int	check_eat_count(t_philo *philo)
{
	if (!philo->sim->p.has_goal)
		return (0);
	if (increase_eat_count(philo) < philo->sim->p.goal)
		return (0);
	set_alive(philo, 0);
	return (1);
}

void	*routine_philo(void *p)
{
	t_philo *const	philo = p;

	pthread_mutex_lock(&philo->sim->start_mutex);
	pthread_mutex_unlock(&philo->sim->start_mutex);
	if (philo->id % 2)
		usleep(100);
	while (is_running(philo->sim) && is_alive(philo))
	{
		pthread_mutex_lock(&philo->fork_left);
		philo_log(philo, ACTION_FORK);
		pthread_mutex_lock(philo->fork_right);
		philo_log(philo, ACTION_FORK);
		philo_log(philo, ACTION_EAT);
		usleep(philo->sim->p.time_eat * 1000);
		set_last_eat(philo, now());
		pthread_mutex_unlock(&philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		if (check_eat_count(philo))
			break ;
		philo_log(philo, ACTION_SLEEP);
		usleep(philo->sim->p.time_sleep * 1000);
		philo_log(philo, ACTION_THINK);
	}
	set_alive(philo, 0);
	return (NULL);
}

static int	routine_monitor_philo(t_philo *philo)
{
	t_time	last_eat;

	if (is_alive(philo))
	{
		last_eat = get_last_eat(philo);
		if (now() >= last_eat + philo->sim->p.time_die)
		{
			philo_log(philo, NULL);
			return (1);
		}
	}
	return (0);
}

static void	*unlock_mutexes(t_sim *sim)
{
	unsigned int	n;

	n = 0;
	while (n < sim->p.philo_count)
		pthread_mutex_unlock(&sim->philos[n++].fork_left);
	return (NULL);
}

void	*routine_monitor(void *s)
{
	t_sim *const	sim = s;
	unsigned int	n;

	pthread_mutex_lock(&sim->start_mutex);
	pthread_mutex_unlock(&sim->start_mutex);
	while (is_running(sim) && get_alive_count(sim) > 0)
	{
		n = 0;
		while (n < sim->p.philo_count)
			if (routine_monitor_philo(&sim->philos[n++]))
				return (unlock_mutexes(sim));
		usleep(100);
	}
	return (unlock_mutexes(sim));
}
