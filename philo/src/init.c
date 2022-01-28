/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 07:52:40 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/28 05:10:54 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <unistd.h>

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
	philo->eat_count = 0;
	if (pthread_mutex_init(&philo->alive_lock, NULL)
		|| pthread_mutex_init(&philo->last_eat_lock, NULL)
		|| pthread_mutex_init(&philo->eat_count_lock, NULL))
		return (write(2, ERROR_MUTEX "\n", sizeof ERROR_MUTEX) && 0);
	init_philo_forks(philo);
	if (pthread_create(&philo->thread, NULL, routine_philo, philo))
		return (write(2, ERROR_THREAD "\n", sizeof ERROR_THREAD) && 0);
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
			return (write(2, ERROR_MUTEX "\n", sizeof ERROR_MUTEX) && 0);
	if (pthread_mutex_init(&sim->write_mutex, NULL)
		|| pthread_mutex_init(&sim->running_lock, NULL)
		|| pthread_mutex_init(&sim->start_lock, NULL))
		return (write(2, ERROR_MUTEX "\n", sizeof ERROR_MUTEX) && 0);
	pthread_mutex_lock(&sim->start_lock);
	if (pthread_create(&sim->monitor_thread, NULL, routine_monitor, sim))
		return (write(2, ERROR_THREAD "\n", sizeof ERROR_THREAD) && 0);
	return (1);
}

int	init(t_sim *sim)
{
	if (sim->philo_count == 0)
		return (write(2, ERROR_COUNT "\n", sizeof ERROR_COUNT) && 0);
	sim->forks = malloc(sizeof (*sim->forks) * sim->philo_count);
	sim->philos = malloc(sizeof (*sim->philos) * sim->philo_count);
	if (!sim->forks || !sim->philos)
		return (write(2, ERROR_MALLOC "\n", sizeof ERROR_MALLOC) && 0);
	return (init_pthread(sim) && init_philos(sim) && (sim->running = 1));
}
