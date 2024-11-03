/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:12:43 by chourri           #+#    #+#             */
/*   Updated: 2024/09/29 10:22:04 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(char *str)
{
	long int	result;
	int			i;
	int			sign;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		if ((result * sign) > INT_MAX)
			return (-1);
		i++;
	}
	if (str[i] && (str[i] < '0' || str[i] > '9'))
		return (-1);
	return (result * sign);
}

static size_t	ft_strlcpy(char *dest, char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (strlen(src));
	if (dstsize > 0)
	{
		while ((i < dstsize - 1) && src[i])
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (strlen(src));
}

static char	*ft_strchr(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char )c)
			return ((char *)(str + i));
		i++;
	}
	if ((char )c == '\0')
		return (str + i);
	return (NULL);
}

char	*ft_strtrim(char *s1, char *set)
{
	char		*start;
	char		*end;
	char		*buffer;

	if (!s1 || !set)
		return (NULL);
	start = s1;
	end = s1 + strlen(s1);
	while (*start && ft_strchr(set, *start))
		start++;
	while (end > start && ft_strchr(set, *(end - 1)))
		end--;
	buffer = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!buffer)
		return (NULL);
	ft_strlcpy(buffer, start, end - start + 1);
	return (buffer);
}
