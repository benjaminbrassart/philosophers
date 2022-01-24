/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 09:22:18 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/24 17:16:43 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	run(t_sim *sim)
{
	unsigned int	n;

	sim->start_time = now();
	n = 0;
	while (n < sim->philo_count)
		sim->philos[n++].last_eat = sim->start_time;
	pthread_mutex_unlock(&sim->start_lock);
	n = 0;
	while (n < sim->philo_count)
		pthread_join(sim->philos[n++].thread, NULL);
	pthread_join(sim->monitor_thread, NULL);
}
