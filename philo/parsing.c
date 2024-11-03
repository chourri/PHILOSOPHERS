/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:05:30 by chourri           #+#    #+#             */
/*   Updated: 2024/09/28 17:52:15 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_empty(int ac, char **av)
{
	int		i;
	char	*trimmed;

	i = 0;
	trimmed = NULL;
	while (++i < ac)
	{
		trimmed = ft_strtrim(av[i], " \t");
		if (trimmed == NULL || *trimmed == '\0')
			return (free(trimmed), 1);
		av[i] = trimmed;
	}
	return (0);
}

static int	check_args(int ac, char **av)
{
	int	i;
	int	nbr;

	i = 1;
	while (i < ac)
	{
		nbr = ft_atoi(av[i]);
		if (nbr < 0)
			return (1);
		i++;
	}
	return (0);
}

int	parse_args(int ac, char **av)
{
	if ((ac != 5 && ac != 6))
		return (write (2, "invalid args!\n", 14), 1);
	if (ft_atoi(av[1]) == 0)
		return (1);
	else if (is_empty(ac, av) || check_args(ac, av))
		return (write (2, "invalid args!\n", 14), 1);
	return (0);
}
