/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngharian <ngharian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:57:28 by ngharian          #+#    #+#             */
/*   Updated: 2024/12/29 13:05:55 by ngharian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_monitoring(t_philo *philos, t_info info, int i)
{
	uint64_t	time;
	int			ret;

	ret = 0;
	++i;
	pthread_mutex_lock(&philos->finish_eat_mutex);
	pthread_mutex_lock(&philos->meal_time_mutex);
	time = get_time_ms() - info.start_time;
	if (time - ((*philos).last_meal) > info.die_time + 2 \
			&& (*philos).finish_eating != 1)
	{
		pthread_mutex_lock(philos->death_mutex);
		*philos->is_dead = 1;
		pthread_mutex_unlock(philos->death_mutex);
		pthread_mutex_lock(philos->print_mutex);
		printf(DEAD, get_time_ms() - info.start_time, (*philos).id);
		pthread_mutex_unlock(philos->print_mutex);
		ret = 1;
	}
	pthread_mutex_unlock(&philos->finish_eat_mutex);
	pthread_mutex_unlock(&philos->meal_time_mutex);
	return (ret);
}

static int	is_philo_filled(t_philo *philos)
{
	int	ret;

	ret = 1;
	pthread_mutex_lock(&philos->finish_eat_mutex);
	if ((*philos).finish_eating == 0)
		ret = 0;
	pthread_mutex_unlock(&philos->finish_eat_mutex);
	return (ret);
}

static int	thread_fail(t_philo *philo, t_philo *philos, t_info info, \
				pthread_mutex_t *forks)
{
	pthread_mutex_lock(philo->death_mutex);
	*philo->is_dead = 1;
	pthread_mutex_unlock(philo->death_mutex);
	pthread_mutex_lock(philo->print_mutex);
	write(2, "Error: thread initialisation\n", 29);
	pthread_mutex_unlock(philo->print_mutex);
	ft_free(forks, philos, info, -1);
	return (0);
}

int	start_threading(pthread_mutex_t *forks, t_philo *philos, \
				t_info info, int i)
{
	info.all_eated = 1;
	while (++i < info.philo_num)
	{
		if (pthread_create(&philos[i].tid, NULL, &thread_routine, \
						(void *)&philos[i]) != 0)
			return (thread_fail(&philos[i], philos, info, forks));
	}
	i = -1;
	while (++i < info.philo_num)
	{
		if (ft_monitoring(&philos[i], info, i))
			return (ft_free(forks, philos, info, -1));
		if (is_philo_filled(&philos[i]) != 1)
			info.all_eated = 0;
		if (i == info.philo_num - 1 && info.all_eated == 0)
		{
			info.all_eated = 1;
			i = -1;
		}
	}
	return (ft_free(forks, philos, info, -1));
}
