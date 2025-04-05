#include <main.h>

t_philo *init_philos(int count, t_data *data)
{
	int i;
	t_philo *arr;

	arr = malloc(sizeof(t_philo) * (count));
	i = -1;
	while (++i < count)
	{
		arr[i].index = i;
		arr[i].meal_count = 0;
		arr[i].state = EATING;
		arr[i].data = data;
	}
	return (arr);
}

t_philo *init_data(char **args, t_data *data)
{
	int i;

	data->count = ft_atoi(*args++);
	data->tt_die = ft_atoi(*args++);
	data->tt_eat = ft_atoi(*args++);
	data->tt_sleep = ft_atoi(*args++);
	data->eat_min = -1;
	if (*args)
		data->eat_min = ft_atoi(*args);
	data->forks = malloc(data->count * sizeof(pthread_mutex_t));
	i = 0;
	while (i < data->count)
		pthread_mutex_init(data->forks + i++, NULL);
	return (init_philos(data->count, data));
}

pthread_t *init_threads(int count)
{
	pthread_t *arr;

	arr = malloc(count * sizeof(pthread_t));
	return (arr);
}

void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		eating(philo->data, philo->index);
		sleeping(philo->data, philo->index);
	}
}

int is_dead(t_philo *philo)
{
	int diff;

	diff = time(NULL) - philo->last_meal;
	if (diff > philo->data->tt_die)
		return (1);
	return (0);
}

void *monitor(void *arg)
{
	int i;
	t_philo *philos;
	t_data *data;

	philos = (t_philo *)arg;
	data = philos->data;
	while (1)
	{
		i = -1;
		while (++i < data->count)
		{
			if (is_dead(philos + i))
				break ;
		}
	}
}

int simulate(t_data *data, t_philo *philos, pthread_t *threads)
{
	pthread_t monitor_th;
	int i;

	i = -1;
	puts("test1");
	while (++i < data->count)
		pthread_create(threads + i, NULL, routine, philos + i);
	pthread_create(&monitor_th, NULL, monitor, philos + i);
	while (i)
		pthread_join(threads[i--], NULL);
	return (0);
}

int main(int ac, char **av)
{
	t_data data;
	t_philo *philos;
	pthread_t *threads;

	if (ac != 5)
		return (1);
	philos = init_data(av + 1, &data);
	threads = malloc(data.count * sizeof(pthread_t));
	simulate(&data, philos, threads);
	return (0);
}