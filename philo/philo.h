/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 01:45:14 by bbrassar          #+#    #+#             */
/*   Updated: 2021/12/25 09:06:01 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

# define ACTION_FORK "has taken a fork"
# define ACTION_EAT "is eating"
# define ACTION_SLEEP "is sleeping"
# define ACTION_THINK "is thinking"
# define ACTION_DEAD "died"

typedef struct s_sim	t_sim;
typedef struct s_philo	t_philo;

struct s_sim
{
	unsigned int		philo_count;
	unsigned int		time_die;
	unsigned int		time_eat;
	unsigned int		time_sleep;
	unsigned int		goal;
	int					has_goal;
	unsigned int		fork_count;
	pthread_t			monitor_thread;
	pthread_mutex_t		*forks;
	t_philo				*philos;
	pthread_mutex_t		talk_lock;
	int					running;
	pthread_mutex_t		running_lock;
	pthread_mutex_t		start_lock;
};

struct s_philo
{
	t_sim				*sim;
	unsigned int		id;
	pthread_t			thread;
	pthread_mutex_t		*fork1;
	pthread_mutex_t		*fork2;
	int					alive;
	pthread_mutex_t		alive_lock;
	int					eating;
	pthread_mutex_t		eating_lock;
	unsigned long long	last_eat;
	pthread_mutex_t		last_eat_lock;
};

unsigned long long	now(void);

int					init(t_sim *sim);

void				run(t_sim *sim);

void				*routine_philo(void *p);

void				*routine_monitor(void *s);

void				philo_log(t_philo *philo, char const *action);

int					is_running(t_sim *sim);

void				set_running(t_sim *sim, int running);

int					is_alive(t_philo *philo);

int					is_eating(t_philo *philo);

void				set_eating(t_philo *philo, int eating);

unsigned long long	get_last_eat(t_philo *philo);

void				set_last_eat(t_philo *philo, unsigned long long last_eat);

#endif
