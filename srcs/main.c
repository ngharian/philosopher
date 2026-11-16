/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngharian <ngharian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:10:39 by ngharian          #+#    #+#             */
/*   Updated: 2024/12/28 12:48:02 by ngharian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_init_data(t_info *info, char **argv, int argc)
{
	int	e_time;
	int	s_time;
	int	d_time;

	(*info).philo_num = ft_atoi(argv[1]);
	d_time = ft_atoi(argv[2]);
	e_time = ft_atoi(argv[3]);
	s_time = ft_atoi(argv[4]);
	(*info).start_time = get_time_ms();
	if (argc == 6)
		(*info).eat_num = ft_atoi(argv[5]);
	else
		(*info).eat_num = -1;
	if ((*info).philo_num > 200 || (*info).philo_num <= 0
		|| d_time < 60 || e_time < 60
		|| s_time < 60 || ((*info).eat_num <= 0 && argc == 6))
	{
		write(2, "Error: bad arguments!\n", 22);
		return (1);
	}
	(*info).die_time = (uint64_t)d_time;
	(*info).eat_time = (uint64_t)e_time;
	(*info).sleep_time = (uint64_t)s_time;
	return (0);
}

static int	verif_input(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
	{
		write(2, "Error: invalid number of arguments!\n", 36);
		return (1);
	}
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < 48 || argv[i][j] > 57 || ft_strlen(argv[i]) > 10)
			{
				write(2, "Error: bad arguments!\n", 22);
				return (1);
			}
			++j;
		}
		++i;
	}
	return (0);
}

static void	*one_routine(void *data)
{
	t_info	*info;

	info = (t_info *)data;
	pthread_mutex_lock(&info->one_fork);
	printf(M_FORK, get_time_ms() - (*info).start_time, 1);
	usleep((*info).die_time * 1000);
	pthread_mutex_unlock(&info->one_fork);
	printf(DEAD, get_time_ms() - (*info).start_time, 1);
	return (NULL);
}

static int	one_case(t_info info)
{
	pthread_t	tid;

	if (pthread_mutex_init(&info.one_fork, NULL) != 0)
	{
		write(2, "Error: Mutex initialisation\n", 28);
		return (1);
	}
	if (pthread_create(&tid, NULL, &one_routine, \
						(void *)&info) != 0)
	{
		pthread_mutex_destroy(&info.one_fork);
		return (1);
	}
	pthread_join(tid, NULL);
	pthread_mutex_destroy(&info.one_fork);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_info	info;

	if (verif_input(argc, argv))
		return (1);
	if (ft_init_data(&info, argv, argc))
		return (1);
	if (info.philo_num == 1)
		return (one_case(info));
	if (pthread_mutex_init(&info.print_mutex, NULL) != 0 \
	|| pthread_mutex_init(&info.death_mutex, NULL) != 0)
	{
		write(2, "Error: Mutex initialisation\n", 28);
		return (1);
	}
	if (ft_start(info))
		return (1);
	return (0);
}
