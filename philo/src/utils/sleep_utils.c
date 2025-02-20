/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macorso <macorso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 05:37:56 by macorso           #+#    #+#             */
/*   Updated: 2025/02/20 12:37:27 by macorso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	smart_sleep(t_philo *philo)
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
	while (current_time - philo->info->start_time < philo->info->sleep_time)
	{
		if (philo->info->someone_died)
			break ;
		usleep(100);
		current_time = get_time_ms();
	}
	smart_print(philo, " is sleeping\n");
	return (0);
}

void	smart_wait(long time)
{
	long	current_time;

	current_time = get_time_ms();
	while (get_time_ms() - current_time < time)
		usleep(100);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}