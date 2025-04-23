/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macorso <macorso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 05:37:56 by macorso           #+#    #+#             */
/*   Updated: 2025/04/23 13:10:09 by macorso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	smart_sleep(t_philo *philo)
{
	long	start_time;
	long	current;

	if (smart_print(philo, " is sleeping\n"))
		return (1);
	start_time = get_time_ms();
	while (1)
	{
		current = get_time_ms();
		if (current - start_time >= philo->info->sleep_time)
			break ;
		pthread_mutex_lock(&philo->info->death);
		if (philo->info->someone_died)
		{
			pthread_mutex_unlock(&philo->info->death);
			return (1);
		}
		pthread_mutex_unlock(&philo->info->death);
		usleep(100);
	}
	return (0);
}

void	smart_wait(long wait_time)
{
	long	start;
	long	current;

	start = get_time_ms();
	while (1)
	{
		current = get_time_ms();
		if (current - start >= wait_time)
			break ;
		usleep(100);
	}
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
