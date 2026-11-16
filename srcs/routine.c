/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngharian <ngharian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 18:52:02 by ngharian          #+#    #+#             */
/*   Updated: 2024/12/29 13:05:05 by ngharian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	sec_fork(t_philo *philo, int id, int ret)
{
	if ((*philo).id % 2 == 0)
	{
		pthread_mutex_lock((*philo).l_fork);
		ret = print_message(id, M_FORK, philo->print_mutex, philo);
		if (ret == 1)
		{
			pthread_mutex_unlock((*philo).r_fork);
			pthread_mutex_unlock((*philo).l_fork);
		}
		return (ret);
	}
	else
	{
		pthread_mutex_lock((*philo).r_fork);
		ret = print_message(id, M_FORK, philo->print_mutex, philo);
		if (ret == 1)
		{
			pthread_mutex_unlock((*philo).r_fork);
			pthread_mutex_unlock((*philo).l_fork);
		}
		return (ret);
	}
}

static int	fst_fork(t_philo *philo, int id, int ret)
{
	if ((*philo).id % 2 == 0)
	{
		pthread_mutex_lock((*philo).r_fork);
		ret = print_message(id, M_FORK, philo->print_mutex, philo);
		if (ret == 1)
			pthread_mutex_unlock((*philo).r_fork);
		return (ret);
	}
	else
	{
		pthread_mutex_lock((*philo).l_fork);
		ret = print_message(id, M_FORK, philo->print_mutex, philo);
		if (ret == 1)
			pthread_mutex_unlock((*philo).l_fork);
		return (ret);
	}
}

static int	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_time_mutex);
	(*philo).last_meal = get_time_ms() - (*philo).start_time;
	pthread_mutex_unlock(&philo->meal_time_mutex);
	(*philo).meal_number += 1;
	if (print_message((*philo).id, M_EAT, philo->print_mutex, philo))
	{
		pthread_mutex_unlock((*philo).r_fork);
		pthread_mutex_unlock((*philo).l_fork);
		return (1);
	}
	usleep((*philo).eat_time * 1000);
	pthread_mutex_unlock((*philo).r_fork);
	pthread_mutex_unlock((*philo).l_fork);
	return (0);
}

static int	ft_sleep(t_philo *philo)
{
	if (print_message((*philo).id, M_SLEEP, philo->print_mutex, philo))
		return (1);
	usleep((*philo).sleep_time * 1000);
	return (0);
}

void	*thread_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	pthread_mutex_lock(philo->death_mutex);
	while (*philo->is_dead != 1 && (*philo).meal_number != (*philo).to_eat)
	{
		pthread_mutex_unlock(philo->death_mutex);
		if (fst_fork(philo, (*philo).id, 0) || sec_fork(philo, (*philo).id, 0))
			return (NULL);
		if (ft_eat(philo))
			return (NULL);
		if ((*philo).meal_number == (*philo).to_eat)
		{
			pthread_mutex_lock(&philo->finish_eat_mutex);
			(*philo).finish_eating = 1;
			pthread_mutex_unlock(&philo->finish_eat_mutex);
			return (NULL);
		}
		ft_sleep(philo);
		if (print_message((*philo).id, M_THINK, philo->print_mutex, philo))
			return (NULL);
		pthread_mutex_lock(philo->death_mutex);
	}
	pthread_mutex_unlock(philo->death_mutex);
	return (NULL);
}
