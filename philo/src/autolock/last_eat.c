/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_eat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 04:17:47 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/28 05:44:57 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_time	get_last_eat(t_philo *philo)
{
	t_time	last_eat;

	pthread_mutex_lock(&philo->last_eat_lock);
	last_eat = philo->last_eat;
	pthread_mutex_unlock(&philo->last_eat_lock);
	return (last_eat);
}

void	set_last_eat(t_philo *philo, t_time last_eat)
{
	pthread_mutex_lock(&philo->last_eat_lock);
	philo->last_eat = last_eat;
	pthread_mutex_unlock(&philo->last_eat_lock);
}
