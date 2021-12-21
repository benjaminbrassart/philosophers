/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 01:45:14 by bbrassar          #+#    #+#             */
/*   Updated: 2021/12/21 09:40:07 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_sim	t_sim;
typedef struct s_philo	t_philo;

struct s_sim
{
	unsigned int	philo_count;
	unsigned int	time_die;
	unsigned int	time_eat;
	unsigned int	time_sleep;
	unsigned int	goal;
	int				has_goal;
	unsigned int	fork_count;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_mutex_t	talk_lock;
};

struct s_philo
{
	t_sim			*sim;
	unsigned int	id;
	pthread_t		thread;
	pthread_mutex_t	lock;
};

unsigned long long	now(void);

int					init(t_sim *sim);

void				run(t_sim *sim);

void				*routine_philo(void *p);

void				*routine_manager(void *s);

#endif
