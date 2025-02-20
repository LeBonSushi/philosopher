/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macorso <macorso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 06:15:34 by macorso           #+#    #+#             */
/*   Updated: 2025/02/20 12:42:51 by macorso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->death);
	if (philo->info->someone_died)
	{
		pthread_mutex_unlock(&philo->info->death);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->death);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->fork_right);
		smart_print(philo, " has taken a fork\n");
		pthread_mutex_lock(philo->fork_left);
		smart_print(philo, " has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(philo->fork_left);
		smart_print(philo, " has taken a fork\n");
		pthread_mutex_lock(philo->fork_right);
		smart_print(philo, " has taken a fork\n");
	}
	return (0);
}

int	eat(t_philo *philo)
{
	long	current_time;

	pthread_mutex_lock(&philo->info->death);
	if (philo->info->someone_died)
	{
		pthread_mutex_unlock(&philo->info->death);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->death);
	current_time = get_time_ms();
	smart_print(philo, " is eating\n");
	smart_wait(philo->info->eat_time);
    pthread_mutex_lock(&philo->last_meal_mutex);
    philo->last_meal_time = current_time;
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->last_meal_mutex);
	return (0);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}
int	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->death);
	if (philo->info->someone_died)
	{
		pthread_mutex_unlock(&philo->info->death);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->death);
	smart_print(philo, " is thinking\n");
	return (0);
}

int	verify_death(t_philo *philo)
{
	
	if (take_forks(philo))
		return (1);
	if (eat(philo))
		return (1);
	drop_forks(philo);
	if (smart_sleep(philo))
		return (1);
	if (thinking(philo))
		return (1);
	return (0);
}


void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	int	id;

	philo = (t_philo *)arg;
	id = philo->id;

	while (1)
	{
		if (verify_death(philo))
			break ;
	}
	return (NULL);
}
