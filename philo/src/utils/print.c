/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macorso <macorso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:21:32 by macorso           #+#    #+#             */
/*   Updated: 2025/02/20 12:09:30 by macorso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	smart_print(t_philo	*philo, char *msg)
{
	long	current_time;

	// pthread_mutex_lock(&philo->info->death);
	// if (philo->info->someone_died)
	// {
	// 	pthread_mutex_unlock(&philo->info->death);
	// 	return ;
	// }
	// pthread_mutex_unlock(&philo->info->death);

	pthread_mutex_lock(&philo->info->print);
	current_time = get_time_ms() - philo->info->start_time;
	printf("\e[0m\e[1;35m%ld \e[0m\e[1;36m%d \e[0m%s\n", current_time, philo->id, msg);
	pthread_mutex_unlock(&philo->info->print);
}