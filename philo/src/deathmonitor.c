/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deathmonitor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macorso <macorso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:37:57 by macorso           #+#    #+#             */
/*   Updated: 2025/04/22 22:40:42 by macorso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*death_monitor(void *arg)
{
	t_info	*info;

	info = (t_info *)arg;
	while (1)
	{
		if (check_all_philos(info))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
