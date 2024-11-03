/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:15:46 by chourri           #+#    #+#             */
/*   Updated: 2024/09/28 17:39:25 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(t_data *data)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000) - data->start_time);
}

static void	initialize_args(t_data **data, char **av)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	(*data)->start_time = (time.tv_sec * 1000 + time.tv_usec / 1000);
	(*data)->no_philo = ft_atoi(av[1]);
	(*data)->time_to_die = ft_atoi(av[2]);
	(*data)->time_to_eat = ft_atoi(av[3]);
	(*data)->time_to_sleep = ft_atoi(av[4]);
	(*data)->end_simulation = false;
}

int	data_initialization(t_data *data, int ac, char **av)
{
	if (pthread_mutex_init(&data->meal_time, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->msg_mutex, NULL) != 0)
		return (pthread_mutex_destroy(&data->meal_time), 1);
	initialize_args(&data, av);
	data->thread = malloc(sizeof(pthread_t) * data->no_philo);
	if (!data->thread)
	{
		pthread_mutex_destroy(&data->meal_time);
		return (pthread_mutex_destroy(&data->msg_mutex), 1);
	}
	data->forks = malloc(sizeof(pthread_mutex_t) * data->no_philo);
	if (!data->forks)
	{
		free(data->thread);
		free(data);
		pthread_mutex_destroy(&data->meal_time);
		return (pthread_mutex_destroy(&data->msg_mutex), 1);
	}
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
	else
		data->must_eat = -1;
	return (0);
}

static void	destroy_failed_mutexes(int i, t_data *data, t_philo *philo)
{
	int	j;

	j = 0;
	while (j < i)
		pthread_mutex_destroy(&data->forks[j++]);
	pthread_mutex_destroy(&data->msg_mutex);
	pthread_mutex_destroy(&data->meal_time);
	free_ptrs(data->forks, data->thread, data, philo);
}

int	philo_initialization(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->no_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (destroy_failed_mutexes(i, data, philo), 1);
		philo[i].has_eaten = 0;
		philo[i].left_fork = &data->forks[i];
		philo[i].right_fork = &data->forks[(i + 1) % data->no_philo];
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i++].last_meal_time = get_time(data);
	}
	i = -1;
	while (++i < data->no_philo)
	{
		if (pthread_create(&data->thread[i], NULL, routine, &philo[i]) != 0)
			return (write(2, "Thread creation failed\n", 16), 1);
	}
	return (0);
}
