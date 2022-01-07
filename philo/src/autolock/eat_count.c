/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 04:28:46 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/03 04:52:56 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	get_eat_count(t_philo *philo)
{
	unsigned int	eat_count;

	pthread_mutex_lock(&philo->eat_count_lock);
	eat_count = philo->eat_count;
	pthread_mutex_unlock(&philo->eat_count_lock);
	return (eat_count);
}

void	set_eat_count(t_philo *philo, unsigned int eat_count)
{
	pthread_mutex_lock(&philo->eat_count_lock);
	philo->eat_count = eat_count;
	pthread_mutex_unlock(&philo->eat_count_lock);
}

unsigned int	increase_eat_count(t_philo *philo)
{
	unsigned int	eat_count;

	pthread_mutex_lock(&philo->eat_count_lock);
	eat_count = ++philo->eat_count;
	pthread_mutex_unlock(&philo->eat_count_lock);
	return (eat_count);
}
