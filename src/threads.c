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
		usleep(500);
	if (philo->index == philo->data->count - 1 && philo->data->count % 2)
		usleep(1000);
	while (1)
	{
		if (!is_running(philo->data))
			break ;
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

int	is_dead(t_philo *philo)
{
	int	diff;

	diff = get_time() - philo->last_meal;
	if (diff > philo->data->tt_die)
	{
		pthread_mutex_lock(&philo->data->run);
		philo->data->running = 0;
		pthread_mutex_unlock(&philo->data->run);
		return (1);
	}
	return (0);
}

int	simulation_over(t_philo *philos)
{
	int		ate;
	int		i;
	t_data	*data;

	data = philos->data;
	ate = 0;
	i = -1;
	while (++i < data->count)
	{
		if (is_dead(philos + i))
		{
			printf("%ld %s%d died%s\n", get_time() - data->start,
				RED, i + 1, WHT);
			return (1);
		}
		if (data->eat_min != -1 && (*(philos + i)).meal_count == data->eat_min)
			ate++;
	}
	return (ate == data->count);
}
