/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 07:52:40 by bbrassar          #+#    #+#             */
/*   Updated: 2021/12/21 09:40:42 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

static int	init_philo(t_philo *philo, t_sim *sim, unsigned int id)
{
	philo->sim = sim;
	philo->id = id;
	if (pthread_mutex_init(&philo->lock, NULL))
		return (0);
	if (pthread_create(&philo->thread, NULL, NULL, philo))
		return (0);
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

static int	init_forks(t_sim *sim)
{
	unsigned int	n;

	n = 0;
	while (n < sim->fork_count && !pthread_mutex_init(&sim->forks[n], NULL))
		++n;
	return (n == sim->fork_count);
}

static int	init_locks(t_sim *sim)
{
	return (!pthread_mutex_init(&sim->talk_lock, NULL));
}

int	init(t_sim *sim)
{
	if (sim->philo_count == 0)
	{
		printf("Error: There must be at least 1 philosopher\n");
		return (0);
	}
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
	return (init_locks(sim) && init_forks(sim) && init_philos(sim));
}
