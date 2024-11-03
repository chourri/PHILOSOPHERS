/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:32:43 by chourri           #+#    #+#             */
/*   Updated: 2024/09/29 10:21:39 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_data
{
	pthread_t			*thread;
	pthread_mutex_t		*forks;
	pthread_mutex_t		meal_time;
	pthread_mutex_t		msg_mutex;
	int					no_philo;
	int					time_to_die;
	int					time_to_eat;
	unsigned long long	start_time;
	int					time_to_sleep;
	int					must_eat;
	bool				end_simulation;
}					t_data;

typedef struct s_philo
{
	t_data				*data;
	int					id;
	int					has_eaten;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	int					last_meal_time;
}					t_philo;

typedef struct s_monitor
{
	t_data	*data;
	t_philo	*philo;
	int		i;
}			t_monitor;

int		parse_args(int ac, char **av);
long	ft_atoi(char *str);
char	*ft_strtrim(char *s1, char *set);
void	*monitor(void *param);
int		data_initialization(t_data *data, int ac, char **av);
int		philo_initialization(t_philo *philo, t_data *data);
int		get_time(t_data *data);
int		check_end_simulation(t_data *data);
void	*routine(void *param);
void	free_ptrs(void *ptr, void *ptr1, void *ptr2, void *ptr3);

#endif
