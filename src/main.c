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

int single_thread(t_data data)
{
	data.start = get_time();
	pthread_mutex_lock(data.forks);
	print_action(&data, 0, FORK);
	_sleep(data.tt_die, &data);
	printf("%ld %s%d died%s\n", get_time() - data.start, RED, 1, WHT);
	pthread_mutex_unlock(data.forks);
	return (0);
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
	if (data.count == 1)
		return (single_thread(data));
	threads = malloc(data.count * sizeof(pthread_t));
	simulate(&data, philos, threads);
	return (0);
}
