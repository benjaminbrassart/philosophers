/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 01:44:01 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/28 05:17:13 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int	set_param(unsigned int *param, char *arg)
{
	char const		*s = arg;
	unsigned int	value;
	unsigned int	prev;

	value = 0;
	while (*s >= '0' && *s <= '9')
	{
		prev = value;
		value = value * 10 + *s++ - '0';
		if (value < prev)
			return (write(2, ERROR_OVERFLOW "\n", sizeof ERROR_OVERFLOW) && 0);
	}
	if (*s || (s == arg && value == 0))
		return (write(2, ERROR_ARGV "\n", sizeof ERROR_ARGV) && 0);
	*param = value;
	return (1);
}

static int	parse_params(t_sim *sim, int argc, char *argv[])
{
	int	params;

	if (argc != 5 && argc != 6)
		return (write(2, ERROR_ARGC "\n", sizeof ERROR_ARGC) && 0);
	params = (set_param(&sim->p.philo_count, argv[1])
			&& set_param(&sim->p.time_die, argv[2])
			&& set_param(&sim->p.time_eat, argv[3])
			&& set_param(&sim->p.time_sleep, argv[4]));
	if (argc == 6)
	{
		sim->p.has_goal = 1;
		params &= set_param(&sim->p.goal, argv[5]);
	}
	return (params);
}

static int	cleanup(t_sim *sim)
{
	unsigned int	n;

	if (sim->forks)
	{
		n = 0;
		while (n < sim->p.philo_count)
			pthread_mutex_destroy(&sim->forks[n++]);
		free(sim->forks);
	}
	if (sim->philos)
	{
		n = 0;
		while (n < sim->p.philo_count)
			pthread_mutex_destroy(&sim->philos[n++].alive_lock);
		free(sim->philos);
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_sim	sim;
	int		res;

	if (!parse_params(memset(&sim, 0, sizeof sim), argc, argv))
		return (1);
	if (sim.p.has_goal && !sim.p.goal)
		return (0);
	res = init(&sim);
	if (res)
		run(&sim);
	return (cleanup(&sim) && !res);
}
