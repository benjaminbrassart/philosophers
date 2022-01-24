/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 07:52:40 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/24 17:44:22 by bbrassar         ###   ########.fr       */
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
		philo->fork2 = &philo->sim->forks[(id + 1) % philo->sim->philo_count];
	}
	else
	{
		philo->fork2 = &philo->sim->forks[id];
		philo->fork1 = &philo->sim->forks[(id + 1) % philo->sim->philo_count];
	}
}

static int	init_philo(t_philo *philo, t_sim *sim, unsigned int id)
{
	philo->sim = sim;
	philo->id = id;
	philo->alive = 1;
	philo->eating = 0;
	philo->eat_count = 0;
	if (pthread_mutex_init(&philo->alive_lock, NULL)
		|| pthread_mutex_init(&philo->eating_lock, NULL)
		|| pthread_mutex_init(&philo->last_eat_lock, NULL)
		|| pthread_mutex_init(&philo->eat_count_lock, NULL))
		return (printf("Error: Failed to create mutex\n") && 0);
	init_philo_forks(philo);
	if (pthread_create(&philo->thread, NULL, routine_philo, philo))
		return (printf("Error: Failed to create thread\n") && 0);
	return (1);
}

static int	init_philos(t_sim *sim)
{
	unsigned int	n;

	n = 0;
	while (n < sim->philo_count && init_philo(&sim->philos[n], sim, n))
		++n;
	return (n == sim->philo_count);
}

static int	init_pthread(t_sim *sim)
{
	unsigned int	n;

	n = 0;
	while (n < sim->philo_count)
		if (pthread_mutex_init(&sim->forks[n++], NULL))
			return (printf("Error: Failed to create mutex\n") && 0);
	if (pthread_mutex_init(&sim->talk_lock, NULL)
		|| pthread_mutex_init(&sim->running_lock, NULL)
		|| pthread_mutex_init(&sim->start_lock, NULL))
		return (printf("Error: Failed to create mutex\n") && 0);
	pthread_mutex_lock(&sim->start_lock);
	if (pthread_create(&sim->monitor_thread, NULL, routine_monitor, sim))
		return (printf("Error: Failed to create thread\n") && 0);
	return (1);
}

int	init(t_sim *sim)
{
	if (sim->philo_count == 0)
	{
		printf("Error: There must be at least 1 philosopher\n");
		return (0);
	}
	sim->forks = malloc(sizeof (*sim->forks) * sim->philo_count);
	sim->philos = malloc(sizeof (*sim->philos) * sim->philo_count);
	if (!sim->forks || !sim->philos)
		return (printf("Error: Failed to allocate memory\n") && 0);
	return (init_pthread(sim) && init_philos(sim) && (sim->running = 1));
}
