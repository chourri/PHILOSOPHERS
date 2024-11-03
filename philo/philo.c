/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:59:58 by chourri           #+#    #+#             */
/*   Updated: 2024/09/28 17:59:17 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_initialize(t_philo **philo, t_data **data, int ac, char **av)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
		return (1);
	if (data_initialization(*data, ac, av))
		return (1);
	*philo = malloc(sizeof(t_philo) * (*data)->no_philo);
	if (!*philo)
		return (1);
	if (philo_initialization(*philo, *data))
		return (1);
	return (0);
}

static void	free_and_clean(t_philo *philo, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->no_philo)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->meal_time);
	pthread_mutex_destroy(&data->msg_mutex);
	if (philo)
		free(philo);
	if (data->forks)
		free(data->forks);
	if (data->thread)
		free(data->thread);
	if (data)
		free(data);
}

void	free_ptrs(void *ptr1, void *ptr2, void *ptr3, void *ptr4)
{
	if (ptr1)
		free(ptr1);
	if (ptr2)
		free(ptr2);
	if (ptr3)
		free(ptr3);
	if (ptr4)
		free(ptr4);
}

int	main(int ac, char **av)
{
	t_data		*data;
	t_philo		*philo;
	t_monitor	monitor_param;
	pthread_t	monitor_thread;
	int			i;

	data = NULL;
	philo = NULL;
	if (parse_args(ac, av))
		return (1);
	if (ft_initialize(&philo, &data, ac, av))
		return (1);
	monitor_param.data = data;
	monitor_param.philo = philo;
	if (pthread_create(&monitor_thread, NULL, monitor, &monitor_param) != 0)
		return (free_and_clean(philo, data), write(2, "Error !\n", 23), 1);
	i = -1;
	if (pthread_join(monitor_thread, NULL) != 0)
		return (free_and_clean(philo, data), write(2, "Error !\n", 19), 1);
	while (++i < data->no_philo)
	{
		if (pthread_join(data->thread[i], NULL) != 0)
			return (free_and_clean(philo, data), write(2, "Error !\n", 19), 1);
	}
	return (free_and_clean(philo, data), 0);
}
