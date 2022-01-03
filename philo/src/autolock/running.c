/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 04:18:32 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/03 04:18:34 by bbrassar         ###   ########.fr       */
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
