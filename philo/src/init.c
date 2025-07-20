/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchetoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:38:06 by mchetoui          #+#    #+#             */
/*   Updated: 2025/07/13 18:38:07 by mchetoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

t_philo	*init_philos(int count, t_data *data)
{
	int		i;
	t_philo	*arr;

	arr = malloc(sizeof(t_philo) * (count));
	i = -1;
	while (++i < count)
	{
		arr[i].index = i;
		arr[i].meal_count = 0;
		arr[i].data = data;
	}
	return (arr);
}

t_philo	*init_data(char **args, t_data *data)
{
	int	i;

	data->count = parse(*args++);
	data->tt_die = parse(*args++);
	data->tt_eat = parse(*args++);
	data->tt_sleep = parse(*args++);
	if (data->count == -1 || data->tt_die == -1
		|| data->tt_eat == -1 || data->tt_sleep == -1)
		return (NULL);
	data->eat_min = -1;
	if (*args)
	{
		data->eat_min = parse(*args);
		if (data->eat_min == -1)
			return (NULL);
	}
	pthread_mutex_init(&data->run, NULL);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->monitor, NULL);
	data->forks = malloc(data->count * sizeof(pthread_mutex_t));
	i = -1;
	while (++i < data->count)
		pthread_mutex_init(data->forks + i, NULL);
	return (init_philos(data->count, data));
}

pthread_t	*init_threads(int count)
{
	pthread_t	*arr;

	arr = malloc(count * sizeof(pthread_t));
	return (arr);
}
