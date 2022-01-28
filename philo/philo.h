/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 01:45:14 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/28 07:38:27 by bbrassar         ###   ########.fr       */
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

# define ERROR_ARGC "Error: Expected 4 or 5 arguments"
# define ERROR_ARGV "Error: An argument is not an unsigned integer"
# define ERROR_OVERFLOW "Error: An argument overflows UINT_MAX"
# define ERROR_MUTEX "Error: Failed to create mutex"
# define ERROR_THREAD "Error: Failed to create thread"
# define ERROR_COUNT "Error: There must be at least 1 philosopher"
# define ERROR_MALLOC "Error: Failed to allocate memory"

typedef struct s_sim		t_sim;
typedef struct s_philo		t_philo;
typedef unsigned long long	t_time;

struct s_params
{
	unsigned int		philo_count;
	unsigned int		time_die;
	unsigned int		time_eat;
	unsigned int		time_sleep;
	unsigned int		goal;
	int					has_goal;
};

struct s_sim
{
	struct s_params		p;
	pthread_t			monitor_thread;
	t_philo				*philos;
	pthread_mutex_t		write_mutex;
	int					running;
	pthread_mutex_t		running_lock;
	t_time				start_time;
	pthread_mutex_t		start_mutex;
};

struct s_philo
{
	t_sim				*sim;
	unsigned int		id;
	pthread_t			thread;
	pthread_mutex_t		fork_left;
	pthread_mutex_t		*fork_right;
	int					alive;
	pthread_mutex_t		alive_lock;
	t_time				last_eat;
	pthread_mutex_t		last_eat_lock;
	unsigned int		eat_count;
	pthread_mutex_t		eat_count_lock;
};

t_time			now(void);

int				init(t_sim *sim);

void			run(t_sim *sim);

void			*routine_philo(void *p);

void			*routine_monitor(void *s);

void			philo_log(t_philo *philo, char const *action);

int				is_running(t_sim *sim);

void			set_running(t_sim *sim, int running);

int				is_alive(t_philo *philo);

void			set_alive(t_philo *philo, int alive);

unsigned int	get_alive_count(t_sim *sim);

t_time			get_last_eat(t_philo *philo);

void			set_last_eat(t_philo *philo, t_time last_eat);

unsigned int	get_eat_count(t_philo *philo);

void			set_eat_count(t_philo *philo, unsigned int eat_count);

unsigned int	increase_eat_count(t_philo *philo);

#endif
