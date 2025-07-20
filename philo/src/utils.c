/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchetoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:38:15 by mchetoui          #+#    #+#             */
/*   Updated: 2025/07/13 18:38:17 by mchetoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	_sleep(int time, t_data *data)
{
	long	start;
	long	now;
	long	diff;

	start = get_time();
	now = start;
	diff = 0;
	while (diff < time && is_running(data))
	{
		usleep(100);
		now = get_time();
		diff = now - start;
	}
}

int	is_running(t_data *data)
{
	int	running;

	pthread_mutex_lock(&data->run);
	running = data->running;
	pthread_mutex_unlock(&data->run);
	return (running);
}
