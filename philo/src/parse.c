/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchetoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:38:10 by mchetoui          #+#    #+#             */
/*   Updated: 2025/07/13 18:38:11 by mchetoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

long	_atoi(char *str)
{
	int		sign;
	long	result;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		sign *= (44 - *str++);
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str++ - '0');
		if (result * sign > INT_MAX || result * sign < INT_MIN)
			return (result * sign);
	}
	while (*str && *str == ' ')
		str++;
	return (result * sign);
}

int	parse(char *av)
{
	int		out;
	char	*str;

	str = av;
	while (*str)
	{
		if (!(*str >= 48 && *str <= 57))
		{
			write(2, "Invalid input\n", 16);
			return (-1);
		}
		str++;
	}
	out = _atoi(av);
	if (!out || out > INT_MAX || out < INT_MIN)
	{
		write(2, "Invalid input\n", 16);
		return (-1);
	}
	return ((int)out);
}
