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
	int out;
	char *str;

	str = av;
	while (*str)
	{
		if (!(*str >= 48 && *str <= 57))
			return (-1);
		str++;
	}
	out = _atoi(av);
	if (out > INT_MAX || out < INT_MIN)
		return (-1);
	// printf("%d\n", out);
	return ((int)out);
}
