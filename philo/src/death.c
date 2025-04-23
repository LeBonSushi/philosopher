/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macorso <macorso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:57:40 by macorso           #+#    #+#             */
/*   Updated: 2025/04/23 13:12:10 by macorso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_meals(t_info *info, int philos_done)
{
	if (philos_done == info->philo_count && info->num_meals > 0)
	{
		pthread_mutex_lock(&info->death);
		info->someone_died = true;
		pthread_mutex_unlock(&info->death);
		return (1);
	}
	return (0);
}

int	verify_death(t_philo *philo)
{
	if (take_forks(philo))
		return (1);
	if (eat(philo))
	{
		drop_forks(philo);
		return (1);
	}
	drop_forks(philo);
	if (smart_sleep(philo))
		return (1);
	return (thinking(philo));
}

static int	is_philo_dead(t_info *info, int i)
{
	long	current_time;
	long	last_meal;

	pthread_mutex_lock(&info->philo[i].last_meal_mutex);
	current_time = get_time_ms();
	last_meal = info->philo[i].last_meal_time;
	pthread_mutex_unlock(&info->philo[i].last_meal_mutex);
	if (current_time - last_meal > info->death_time)
	{
		pthread_mutex_lock(&info->death);
		info->someone_died = true;
		pthread_mutex_unlock(&info->death);
		pthread_mutex_lock(&info->print);
		printf("%ld %d died\n", current_time - info->start_time,
			info->philo[i].id);
		pthread_mutex_unlock(&info->print);
		return (1);
	}
	return (0);
}

static int	has_philo_finished_eating(t_info *info, int i)
{
	int	current_meals;

	pthread_mutex_lock(&info->philo[i].last_meal_mutex);
	current_meals = info->philo[i].meals_eaten;
	pthread_mutex_unlock(&info->philo[i].last_meal_mutex);
	return (info->num_meals > 0 && current_meals >= info->num_meals);
}

int	check_all_philos(t_info *info)
{
	int	i;
	int	philos_done;

	i = -1;
	philos_done = 0;
	while (++i < info->philo_count)
	{
		if (is_philo_dead(info, i))
			return (1);
		if (has_philo_finished_eating(info, i))
			philos_done++;
	}
	if (check_meals(info, philos_done))
		return (1);
	return (0);
}
