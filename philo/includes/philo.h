/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macorso <macorso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:21:39 by macorso           #+#    #+#             */
/*   Updated: 2025/04/23 13:13:11 by macorso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define _DEFAULT_SOURCE

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_info
{
	long			start_time;
	int				philo_count;
	int				death_time;
	int				eat_time;
	int				sleep_time;
	int				num_meals;
	bool			someone_died;
	struct s_philo	*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
}	t_info;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				meals_eaten;
	long			last_meal_time;
	pthread_mutex_t	last_meal_mutex;
	t_info			*info;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
}	t_philo;

/* Core functions */
t_info	*ft_create_info(int ac, char **av);
int		ft_allocate_resources(t_info *info);
void	ft_init_philo(t_philo *philos, t_info *info);
t_info	*ft_init_info(int ac, char **av);
int		ft_start_simulation(t_info *info);
int		ft_end_simulation(t_info *info);

/* Thread routines */
void	drop_forks(t_philo *philo);
int		take_forks(t_philo *philo);
int		check_all_philos(t_info *info);
int		thinking(t_philo *philo);
void	drop_forks(t_philo *philo);
int		eat(t_philo *philo);
int		thinking(t_philo *philo);
int		verify_death(t_philo *philo);
void	*philosopher_routine(void *arg);
void	*death_monitor(void *arg);

/* Utility functions */
int		ft_atoi(const char *str);
int		smart_print(t_philo *philo, char *msg);
int		smart_sleep(t_philo *philo);
void	smart_wait(long time);
int		ft_error(char *msg);
long	get_time_ms(void);

#endif