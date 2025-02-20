/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macorso <macorso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:57:40 by macorso           #+#    #+#             */
/*   Updated: 2025/02/20 12:13:53 by macorso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*death_monitor(void *arg)
{
	t_info	*info;
	int		i;
	long	current_time;
	int		current_meals;

	info = (t_info *)arg;
	i = -1;
	while (1)
	{
		while (++i < info->philo_count)
		{
			pthread_mutex_lock(&info->philo[i].last_meal_mutex);
			current_time = info->philo[i].last_meal_time;
			current_meals = info->philo[i].meals_eaten;
			pthread_mutex_unlock(&info->philo[i].last_meal_mutex);
			
			pthread_mutex_lock(&info->death);
			if (current_meals == info->num_meals && info->num_meals > 0)
			{
				pthread_mutex_lock(&info->print);
				info->someone_died = true;
				pthread_mutex_unlock(&info->print);
				pthread_mutex_unlock(&info->death);
				return (NULL);
			}
			else if (get_time_ms() - current_time > info->death_time)
			{
				pthread_mutex_lock(&info->print);
				printf("\e[0m\e[1;31m%ld \e[0m\e[1;36m%d \e[0m\e[1;31mdied\n", 
					get_time_ms() - info->start_time, info->philo[i].id);
				info->someone_died = true;
				pthread_mutex_unlock(&info->print);
				pthread_mutex_unlock(&info->death);
				return (NULL);
			}
			pthread_mutex_unlock(&info->death);
		}
		i = -1;
		usleep(1000); // small sleep to prevent high CPU usage
	}
	return (NULL);
}