/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_eat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 04:17:47 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/03 04:17:54 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
