/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 04:18:03 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/03 04:18:08 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
