/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macorso <macorso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:37:26 by macorso           #+#    #+#             */
/*   Updated: 2025/04/22 22:40:38 by macorso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	thinking(t_philo *philo)
{
	if (smart_print(philo, " is thinking\n"))
		return (1);
	usleep(100);
	return (0);
}

void	drop_forks(t_philo *philo)
{
	if (philo->fork_left < philo->fork_right)
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
	}
	else
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
	}
}
