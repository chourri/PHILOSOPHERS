/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:14:59 by chourri           #+#    #+#             */
/*   Updated: 2024/09/28 17:34:24 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_end_simulation(t_data *data)
{
	pthread_mutex_lock(&data->meal_time);
	if (data->end_simulation)
	{
		pthread_mutex_unlock(&data->meal_time);
		return (1);
	}
	pthread_mutex_unlock(&data->meal_time);
	return (0);
}

static bool	is_dead(t_philo *philo, int i)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&philo->data->meal_time);
	if ((get_time(philo->data) - philo[i].last_meal_time)
		> philo->data->time_to_die)
		res = 1;
	pthread_mutex_unlock(&philo->data->meal_time);
	return (res);
}

static int	check_death(t_monitor *monitor, int	*counter)
{
	t_data	*data;
	t_philo	*philo;

	data = monitor->data;
	philo = monitor->philo;
	monitor->i = -1;
	while (++monitor->i < data->no_philo && !check_end_simulation(data))
	{
		if (data->must_eat != -1 && philo->has_eaten >= data->must_eat)
			*counter += 1;
		if (is_dead(philo, monitor->i))
		{
			printf("%d %d died\n", get_time(data), philo->id);
			pthread_mutex_lock(&data->meal_time);
			data->end_simulation = true;
			pthread_mutex_unlock(&data->meal_time);
			return (1);
		}
		usleep(100);
	}
	return (0);
}

void	*monitor(void *param)
{
	t_monitor	*monitor;
	t_data		*data;
	t_philo		*philo;
	int			counter;

	monitor = (t_monitor *)param;
	philo = monitor->philo;
	data = monitor->data;
	if (!monitor || !data || !philo)
		return (NULL);
	while (1)
	{
		counter = 0;
		if (check_end_simulation(data) || check_death(monitor, &counter))
			return (NULL);
		if (counter == data->no_philo)
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
