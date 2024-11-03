/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:16:40 by chourri           #+#    #+#             */
/*   Updated: 2024/09/28 17:31:33 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	good_usleep(t_philo *philo, int time)
{
	int	p;

	p = get_time(philo->data);
	while ((get_time(philo->data) - p)
		< time && !check_end_simulation(philo->data))
	{
		if ((get_time(philo->data) - philo->last_meal_time)
			> philo->data->time_to_die)
			break ;
		usleep(100);
	}
}

static void	ft_print_message(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->msg_mutex);
	usleep(20);
	if ((get_time(philo->data) - philo->last_meal_time)
		> philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->data->msg_mutex);
		return ;
	}
	if (!check_end_simulation(philo->data))
		printf("%d %d %s\n", get_time(philo->data), philo->id, msg);
	pthread_mutex_unlock(&philo->data->msg_mutex);
}

static void	who_start(t_philo *philo)
{
	if (philo->id % 2 == 0)
		good_usleep(philo, philo->data->time_to_eat);
}

static void	update_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_time);
	philo->has_eaten++;
	philo->last_meal_time = get_time(philo->data);
	pthread_mutex_unlock(&philo->data->meal_time);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = param;
	who_start(philo);
	while (!check_end_simulation(philo->data)
		&& (philo->data->must_eat == -1
			|| philo->has_eaten < philo->data->must_eat))
	{
		pthread_mutex_lock(philo->left_fork);
		ft_print_message(philo, "has taken a fork");
		if (philo->data->no_philo == 1)
			return (pthread_mutex_unlock(philo->left_fork), NULL);
		pthread_mutex_lock(philo->right_fork);
		ft_print_message(philo, "has taken a fork");
		ft_print_message(philo, "is eating");
		update_meal(philo);
		good_usleep(philo, philo->data->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		ft_print_message(philo, "is sleeping");
		good_usleep(philo, philo->data->time_to_sleep);
		ft_print_message(philo, "is thinking");
	}
	return (NULL);
}
