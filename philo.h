/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngharian <ngharian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:10:10 by ngharian          #+#    #+#             */
/*   Updated: 2024/12/28 12:15:37 by ngharian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*====================INCLUDES====================*/

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdint.h>
# include <limits.h>

/*====================MACROS====================*/

# define DEAD "%lu %d \033[31mdied\033[0m\n"
# define M_FORK "%lu %d \033[93mhas taken a fork\033[0m\n"
# define M_EAT "%lu %d \033[32mis eating\033[0m\n"
# define M_SLEEP "%lu %d \033[36mis sleeping\033[0m\n"
# define M_THINK "%lu %d \033[35mis thinking\033[0m\n"

/*====================PARSING_STRUCT====================*/

typedef struct s_info
{
	int				philo_num;
	int				eat_num;
	uint64_t		die_time;
	uint64_t		eat_time;
	uint64_t		sleep_time;
	uint64_t		start_time;
	int				all_eated;
	pthread_mutex_t	one_fork;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
}	t_info;

/*====================PHILO_STRUCT====================*/

typedef struct s_philo
{
	int				id;
	int				*is_dead;
	int				meal_number;
	int				finish_eating;
	int				to_eat;
	int				meal_init;
	int				time_init;
	pthread_t		tid;
	uint64_t		sleep_time;
	uint64_t		eat_time;
	uint64_t		last_meal;
	uint64_t		start_time;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	meal_time_mutex;
	pthread_mutex_t	finish_eat_mutex;
	pthread_mutex_t	*death_mutex;
}	t_philo;

/*====================PRIMARY_FUNC====================*/

int			ft_start(t_info info);
void		*thread_routine(void *data);
int			start_threading(pthread_mutex_t *forks, t_philo *philos, \
					t_info info, int i);

/*====================UTILS_FUNC====================*/

int			ft_atoi(char *str);
int			ft_strlen(char *str);
int			ft_free(pthread_mutex_t *forks, t_philo *philos, t_info info, \
					int i);
uint64_t	get_time_ms(void);
int			print_message(int id, char *message, pthread_mutex_t *print_mutex, \
						t_philo *philo);

#endif