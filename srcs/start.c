/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngharian <ngharian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:07:30 by ngharian          #+#    #+#             */
/*   Updated: 2024/12/29 12:28:43 by ngharian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static pthread_mutex_t	*init_forks(t_info info)
{
	int				i;
	pthread_mutex_t	*forks;

	i = -1;
	forks = malloc(info.philo_num * sizeof(pthread_mutex_t));
	if (!forks)
	{
		write(2, "Error: Malloc failed\n", 21);
		return (NULL);
	}
	while (++i < info.philo_num)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			write(2, "Error: Mutex initialisation\n", 28);
			while (--i >= 0)
				pthread_mutex_destroy(&forks[i]);
			free(forks);
			ft_free(NULL, NULL, info, -1);
			return (NULL);
		}
	}
	return (forks);
}

static t_philo	ft_fill_philos(t_philo philos, int i, t_info info)
{
	philos.id = i + 1;
	philos.tid = 0;
	philos.meal_number = 0;
	philos.to_eat = info.eat_num;
	philos.start_time = info.start_time;
	philos.finish_eating = 0;
	philos.eat_time = info.eat_time;
	philos.sleep_time = info.sleep_time;
	philos.last_meal = 0;
	return (philos);
}

static int	init_mutexes(t_philo *philos)
{
	(*philos).meal_init = 0;
	(*philos).time_init = 0;
	if (pthread_mutex_init(&philos->meal_time_mutex, NULL) != 0)
	{
		write(2, "Error: Mutex initialisation\n", 28);
		return (1);
	}
	(*philos).meal_init = 1;
	if (pthread_mutex_init(&philos->finish_eat_mutex, NULL) != 0)
	{
		write(2, "Error: Mutex initialisation\n", 28);
		return (1);
	}
	(*philos).time_init = 1;
	return (0);
}

static t_philo	*ft_init_philos(pthread_mutex_t	*forks, \
								t_philo *philos, t_info info)
{
	int				i;

	i = -1;
	while (++i < (info).philo_num)
	{
		philos[i] = ft_fill_philos(philos[i], i, info);
		if (philos[i].id == 1 && (info).philo_num > 1)
			philos[i].l_fork = &forks[(info).philo_num - 1];
		else if (philos[i].id > 1)
			philos[i].l_fork = &forks[i - 1];
		philos[i].r_fork = &forks[i];
		philos[i].print_mutex = &info.print_mutex;
		philos[i].death_mutex = &info.death_mutex;
		if (init_mutexes(&philos[i]))
		{
			ft_free(forks, philos, info, -1);
			return (NULL);
		}
	}
	return (philos);
}

int	ft_start(t_info info)
{
	pthread_mutex_t	*forks;
	t_philo			*philos;
	int				dead;
	int				i;

	dead = 0;
	i = -1;
	forks = init_forks(info);
	if (!forks)
		return (1);
	philos = malloc(sizeof(t_philo) * info.philo_num);
	if (philos == NULL)
	{
		write(2, "Error: Malloc failed\n", 21);
		return (ft_free(forks, NULL, info, -1));
	}
	while (++i < info.philo_num)
		philos[i].is_dead = &dead;
	philos = ft_init_philos(forks, philos, info);
	if (!philos)
		return (1);
	if (start_threading(forks, philos, info, -1) == 0)
		return (1);
	return (0);
}
