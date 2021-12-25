/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autolock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 06:59:57 by bbrassar          #+#    #+#             */
/*   Updated: 2021/12/25 09:05:42 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_running(t_sim *sim)
{
	int	running;

	pthread_mutex_lock(&sim->running_lock);
	running = sim->running;
	pthread_mutex_unlock(&sim->running_lock);
	return (running);
}

void	set_running(t_sim *sim, int running)
{
	pthread_mutex_lock(&sim->running_lock);
	sim->running = running;
	pthread_mutex_unlock(&sim->running_lock);
}

int	is_alive(t_philo *philo)
{
	int	alive;

	pthread_mutex_lock(&philo->alive_lock);
	alive = philo->alive;
	pthread_mutex_unlock(&philo->alive_lock);
	return (alive);
}

int	is_eating(t_philo *philo)
{
	int	eating;

	pthread_mutex_lock(&philo->eating_lock);
	eating = philo->eating;
	pthread_mutex_unlock(&philo->eating_lock);
	return (eating);
}

void	set_eating(t_philo *philo, int eating)
{
	pthread_mutex_lock(&philo->eating_lock);
	philo->eating = eating;
	pthread_mutex_unlock(&philo->eating_lock);
}

unsigned long long	get_last_eat(t_philo *philo)
{
	unsigned long long	last_eat;

	pthread_mutex_lock(&philo->last_eat_lock);
	last_eat = philo->last_eat;
	pthread_mutex_unlock(&philo->last_eat_lock);
	return (last_eat);
}

void	set_last_eat(t_philo *philo, unsigned long long last_eat)
{
	pthread_mutex_lock(&philo->last_eat_lock);
	philo->last_eat = last_eat;
	pthread_mutex_unlock(&philo->last_eat_lock);
}
