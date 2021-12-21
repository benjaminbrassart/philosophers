/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 09:22:18 by bbrassar          #+#    #+#             */
/*   Updated: 2021/12/21 09:29:14 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	run(t_sim *sim)
{
	unsigned int	n;

	n = 0;
	while (n < sim->philo_count)
		pthread_join(sim->philos[n++].thread, NULL);
}
