/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alive.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 04:18:20 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/03 05:13:04 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_alive(t_philo *philo)
{
	int	alive;

	pthread_mutex_lock(&philo->alive_lock);
	alive = philo->alive;
	pthread_mutex_unlock(&philo->alive_lock);
	return (alive);
}

void	set_alive(t_philo *philo, int alive)
{
	pthread_mutex_lock(&philo->alive_lock);
	philo->alive = alive;
	pthread_mutex_unlock(&philo->alive_lock);
}

unsigned int	get_alive_count(t_sim *sim)
{
	unsigned int	alive_count;
	unsigned int	n;

	alive_count = 0;
	n = 0;
	while (n < sim->philo_count)
	{
		if (is_alive(&sim->philos[n]))
			++alive_count;
		++n;
	}
	return (alive_count);
}
