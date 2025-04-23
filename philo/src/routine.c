/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macorso <macorso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 06:15:34 by macorso           #+#    #+#             */
/*   Updated: 2025/04/22 22:33:44 by macorso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	take_rightfirst(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_right);
	if (smart_print(philo, " has taken a fork\n"))
	{
		pthread_mutex_unlock(philo->fork_right);
		return (1);
	}
	pthread_mutex_lock(philo->fork_left);
	if (smart_print(philo, " has taken a fork\n"))
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return (1);
	}
	return (0);
}

static int	take_leftfirst(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	if (smart_print(philo, " has taken a fork\n"))
	{
		pthread_mutex_unlock(philo->fork_left);
		return (1);
	}
	pthread_mutex_lock(philo->fork_right);
	if (smart_print(philo, " has taken a fork\n"))
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		return (1);
	}
	return (0);
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->death);
	if (philo->info->someone_died)
	{
		pthread_mutex_unlock(&philo->info->death);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->death);
	if (philo->fork_left < philo->fork_right)
	{
		if (take_leftfirst(philo))
			return (1);
	}
	else
	{
		if (take_rightfirst(philo))
			return (1);
	}
	return (0);
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	if (smart_print(philo, " is eating\n"))
		return (1);
	smart_wait(philo->info->eat_time);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (0);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->info->death);
		if (philo->info->someone_died)
		{
			pthread_mutex_unlock(&philo->info->death);
			break ;
		}
		pthread_mutex_unlock(&philo->info->death);
		if (verify_death(philo))
			break ;
	}
	return (NULL);
}
