/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 07:52:40 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/03 04:48:14 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

static void	init_philo_forks(t_philo *philo)
{
	int const	id = philo->id;

	if (id % 2 == 0)
	{
		philo->fork1 = &philo->sim->forks[id];
		philo->fork2 = &philo->sim->forks[(id + 1) % philo->sim->fork_count];
	}
	else
	{
		philo->fork2 = &philo->sim->forks[id];
		philo->fork1 = &philo->sim->forks[(id + 1) % philo->sim->fork_count];
	}
}

static int	init_philo(t_philo *philo, t_sim *sim, unsigned int id)
{
	philo->sim = sim;
	philo->id = id;
	philo->alive = 1;
	philo->alive_lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	philo->eating = 0;
	philo->eating_lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	philo->last_eat = now();
	philo->last_eat_lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	philo->eat_count = 0;
	philo->eat_count_lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	init_philo_forks(philo);
	if (pthread_create(&philo->thread, NULL, routine_philo, philo))
	{
		printf("Error: Failed to create thread\n");
		return (0);
	}
	return (1);
}

static void	init_philos(t_sim *sim)
{
	unsigned int	n;

	n = 0;
	while (n < sim->philo_count && init_philo(&sim->philos[n], sim, n))
		++n;
}

static int	init_pthread(t_sim *sim)
{
	unsigned int	n;

	n = 0;
	while (n < sim->fork_count)
		sim->forks[n++] = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	sim->talk_lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	sim->running_lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	sim->start_lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&sim->start_lock);
	if (pthread_create(&sim->monitor_thread, NULL, routine_monitor, sim))
	{
		printf("Error: Failed to create thread\n");
		return (0);
	}
	return (1);
}

int	init(t_sim *sim)
{
	if (sim->philo_count == 0)
	{
		printf("Error: There must be at least 1 philosopher\n");
		return (0);
	}
	sim->running = 1;
	sim->fork_count = sim->philo_count;
	if (sim->philo_count == 1)
		++sim->fork_count;
	sim->forks = malloc(sizeof (*sim->forks) * sim->fork_count);
	sim->philos = malloc(sizeof (*sim->philos) * sim->philo_count);
	if (!sim->forks || !sim->philos)
	{
		printf("Error: Failed to allocate memory\n");
		return (0);
	}
	if (!init_pthread(sim))
		return (0);
	init_philos(sim);
	return (1);
}
