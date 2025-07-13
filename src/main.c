/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchetoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:38:08 by mchetoui          #+#    #+#             */
/*   Updated: 2025/07/13 18:38:09 by mchetoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

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

void	cleanup(t_data *data, t_philo *philos, pthread_t *threads, int *ret)
{
	int	i;

	i = -1;
	while (++i < data->count)
		pthread_mutex_destroy(data->forks + i);
	free(philos);
	free(data->forks);
	free(threads);
	free(ret);
}

int	main(int ac, char **av)
{
	t_data		data;
	t_philo		*philos;
	pthread_t	*threads;

	if (ac < 5 || ac > 6)
	{
		write(2, "Invalid input\n", 16);
		return (1);
	}
	philos = init_data(av + 1, &data);
	if (!philos)
		return (1);
	threads = malloc(data.count * sizeof(pthread_t));
	simulate(&data, philos, threads);
	return (0);
}
