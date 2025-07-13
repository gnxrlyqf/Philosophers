/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchetoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:38:12 by mchetoui          #+#    #+#             */
/*   Updated: 2025/07/13 18:38:14 by mchetoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

void	*monitor(void *arg)
{
	t_philo	*philos;
	t_data	*data;

	philos = (t_philo *)arg;
	data = philos->data;
	while (1)
	{
		usleep(100);
		if (simulation_over(philos))
			break ;
	}
	return (NULL);
}

void	simulate(t_data *data, t_philo *philos, pthread_t *threads)
{
	pthread_t	monitor_th;
	int			i;
	int			*ret;

	data->start = get_time();
	data->running = 1;
	i = -1;
	while (++i < data->count)
		pthread_create(threads + i, NULL, routine, philos + i);
	pthread_create(&monitor_th, NULL, monitor, philos);
	pthread_join(monitor_th, (void **)&ret);
	pthread_mutex_lock(&data->run);
	data->running = 0;
	pthread_mutex_unlock(&data->run);
	while (--i > -1)
		pthread_join(threads[i], NULL);
	cleanup(data, philos, threads, ret);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal = get_time();
	if (philo->index % 2 != 0)
	{
		usleep(500);
		if (philo->index == philo->data->count - 1 && philo->data->count % 2)
			usleep(1000);
	}
	while (is_running(philo->data))
	{
		eating(philo);
		if (!is_running(philo->data))
			break ;
		sleeping(philo);
		if (!is_running(philo->data))
			break ;
		thinking(philo);
	}
	return (NULL);
}

int	is_running(t_data *data)
{
	int	running;

	pthread_mutex_lock(&data->run);
	running = data->running;
	pthread_mutex_unlock(&data->run);
	return (running);
}
