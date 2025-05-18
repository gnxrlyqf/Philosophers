#include <main.h>

long	ft_atoi(char *str)
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

long get_time(void)
{
	struct timeval tv;

	if (!gettimeofday(&tv, NULL))
	{
		//error
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}