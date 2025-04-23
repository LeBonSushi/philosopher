/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macorso <macorso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:21:32 by macorso           #+#    #+#             */
/*   Updated: 2025/04/22 22:41:18 by macorso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	smart_print(t_philo *philo, char *msg)
{
	long	current_time;
	bool	should_print;

	pthread_mutex_lock(&philo->info->death);
	should_print = !philo->info->someone_died;
	pthread_mutex_unlock(&philo->info->death);
	if (!should_print)
		return (1);
	pthread_mutex_lock(&philo->info->print);
	current_time = get_time_ms() - philo->info->start_time;
	printf("\e[0m\e[1;35m%ld \e[0m\e[1;36m%d \e[0m%s", current_time, philo->id,
		msg);
	pthread_mutex_unlock(&philo->info->print);
	return (0);
}
