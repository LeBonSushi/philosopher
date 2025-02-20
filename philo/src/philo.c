/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macorso <macorso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 05:32:17 by macorso           #+#    #+#             */
/*   Updated: 2025/02/20 12:29:45 by macorso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_info	*ft_init_info(int ac, char **av)
{
	t_info	*info;

	if (ac < 5 || ac > 6)
		return (NULL);
	info = ft_create_info(ac, av);
	if (!info)
		return (NULL);
	return (info);
}

int	ft_start_simulation(t_info *info)
{
	int			i;
	pthread_t	monitor;

	if (!info)
		return (ft_error("Invalid philosopher data\n"));
	i = 0;
	while (i < info->philo_count)
	{
		if (pthread_create(&info->philo[i].thread, NULL, philosopher_routine, &info->philo[i]) != 0)
			return (ft_error("Failed to create philosopher thread\n"));
		i++;
	}
	if (pthread_create(&monitor, NULL, death_monitor, info) != 0)
		return (ft_error("Failed to create monitor thread\n"));
	pthread_detach(monitor);
	return (0);
}

int	ft_end_simulation(t_info *info)
{
	int	i;
	int	philo_count;
	
	if (!info)
		return (ft_error("Invalid philosopher data\n"));
	philo_count = info->philo_count;
	i = 0;
	while (i < philo_count)
	{
		pthread_join(info->philo[i].thread, NULL);
		pthread_mutex_destroy(&info->philo[i].last_meal_mutex);
		i++;
	}
	i = 0;
	while (i < philo_count)
	{
		pthread_mutex_destroy(&info->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&info->print);
	pthread_mutex_destroy(&info->death);
	free(info->forks);
	free(info->philo);
	free(info);
	return (0);
}

int	main(int ac, char **av)
{
	t_info	*info;
	
	info = ft_init_info(ac, av);
	if (!info)
		return (ft_error("Failed to initialize philosophers\n"));
	if (info->philo_count > 250)
		return (ft_error("Too many philosophers\n"));
	if (ft_start_simulation(info))
	{
		ft_end_simulation(info);
		return (ft_error("Failed to start simulation\n"));
	}
	ft_end_simulation(info);
	return (0);
}