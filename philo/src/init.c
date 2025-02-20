/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macorso <macorso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 06:20:21 by macorso           #+#    #+#             */
/*   Updated: 2025/02/20 12:30:10 by macorso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_start_info(t_info *info, char **av, int ac)
{
	info->philo_count = ft_atoi(av[1]);
	info->death_time = ft_atoi(av[2]);
	info->eat_time = ft_atoi(av[3]);
	info->sleep_time = ft_atoi(av[4]);
	info->num_meals = -1;
	if (ac == 6)
		info->num_meals = ft_atoi(av[5]);
}

t_info	*ft_create_info(int ac, char **av)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	init_start_info(info, av, ac);
	info->someone_died = false;
	if (info->philo_count <= 0 || info->death_time <= 0
		|| info->eat_time <= 0 || info->sleep_time <= 0
		|| (ac == 6 && info->num_meals <= 0))
		return (free(info), NULL);
	if (!ft_allocate_resources(info))
		return (free(info), NULL);
	pthread_mutex_init(&info->print, NULL);
	pthread_mutex_init(&info->death, NULL);
	ft_init_philo(info->philo, info);
	return (info);
}
int	ft_allocate_resources(t_info *info)
{
	int	i;

	info->philo = malloc(sizeof(t_philo) * info->philo_count);
	if (!info->philo)
		return (0);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->philo_count);
	if (!info->forks)
	{
		free(info->philo);
		return (0);
	}
	i = 0;
	while (i < info->philo_count)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&info->forks[i]);
			free(info->forks);
			free(info->philo);
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_init_philo(t_philo *philos, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_count)
	{
		philos[i].id = i + 1;
		philos[i].info = info;
		philos[i].last_meal_time = get_time_ms();
		philos[i].meals_eaten = 0;
		philos[i].fork_left = &info->forks[(i + 1) % info->philo_count];
		philos[i].fork_right = &info->forks[i];
		pthread_mutex_init(&philos[i].last_meal_mutex, NULL);
		printf("ID: %d FR: %d FL: %d\n", philos[i].id, i, (i + 1) % info->philo_count);
		i++;
	}
	info->start_time = get_time_ms();
}