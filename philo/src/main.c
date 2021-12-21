/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 01:44:01 by bbrassar          #+#    #+#             */
/*   Updated: 2021/12/21 07:03:10 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int	set_param(unsigned int *param, char *arg)
{
	char const	*s = arg;

	while (*s >= '0' && *s <= '9')
		*param = *param * 10 + *s++ - '0';
	if (*s || (s == arg && *param == 0))
	{
		printf("Error: An argument is not an unsigned integer\n");
		return (0);
	}
	return (1);
}

static int	parse_params(t_sim *sim, int argc, char *argv[])
{
	int	params;

	if (argc != 5 && argc != 6)
	{
		printf("Error: Expected 4 or 5 arguments, got %d\n", argc - 1);
		return (0);
	}
	params = (set_param(&sim->philo_count, argv[1])
			&& set_param(&sim->time_die, argv[2])
			&& set_param(&sim->time_eat, argv[3])
			&& set_param(&sim->time_sleep, argv[4]));
	if (argc == 6)
	{
		sim->has_goal = 1;
		params &= set_param(&sim->goal, argv[5]);
	}
	return (params);
}

int	main(int argc, char *argv[])
{
	t_sim	sim;

	if (!parse_params(memset(&sim, 0, sizeof (sim)), argc, argv))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}