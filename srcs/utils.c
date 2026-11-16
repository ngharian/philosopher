/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngharian <ngharian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:29:24 by ngharian          #+#    #+#             */
/*   Updated: 2024/12/29 13:02:21 by ngharian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(char *str)
{
	int			i;
	long int	res;

	i = 0;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		++i;
	if (i == '-' || i == '+')
	{
		if (i == '-')
			return (-1);
		++i;
	}
	while (str[i] != '\0')
	{
		if (str[i] > '9' || str[i] < '0')
			return (-1);
		res *= 10;
		res += str[i] - 48;
		++i;
	}
	if (res > INT_MAX)
		return (-1);
	return (res);
}

uint64_t	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((uint64_t)(tv.tv_sec * 1000) + (uint64_t)(tv.tv_usec / 1000));
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

int	ft_free(pthread_mutex_t *forks, t_philo *philos, t_info info, int i)
{
	if (philos)
	{
		while (++i < info.philo_num)
		{
			if (philos[i].tid != 0)
				pthread_join(philos[i].tid, NULL);
			if (philos[i].time_init == 1)
				pthread_mutex_destroy(&philos[i].meal_time_mutex);
			if (philos[i].meal_init == 1)
				pthread_mutex_destroy(&philos[i].finish_eat_mutex);
			if ((philos[i].time_init == 0 || philos[i].meal_init == 0))
				break ;
		}
		free(philos);
	}
	if (forks)
	{
		i = 0;
		while (i < info.philo_num)
			pthread_mutex_destroy(&forks[i++]);
		free(forks);
	}
	pthread_mutex_destroy(&info.print_mutex);
	pthread_mutex_destroy(&info.death_mutex);
	return (1);
}

int	print_message(int id, char *message, \
				pthread_mutex_t *print_mutex, t_philo *philo)
{
	uint64_t	time;

	time = get_time_ms() - (*philo).start_time;
	pthread_mutex_lock(print_mutex);
	if (philo != NULL)
	{
		pthread_mutex_lock(philo->death_mutex);
		if (*philo->is_dead == 1)
		{
			pthread_mutex_unlock(philo->death_mutex);
			pthread_mutex_unlock(print_mutex);
			return (1);
		}
		pthread_mutex_unlock(philo->death_mutex);
	}
	printf(message, time, id);
	pthread_mutex_unlock(print_mutex);
	return (0);
}
