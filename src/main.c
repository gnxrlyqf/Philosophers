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
	i = -1;
	while (++i < data->count)
		pthread_mutex_init(data->forks + i, NULL);
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
	philo->last_meal = get_time();
	while (1)
	{
		eating(philo);
		sleeping(philo->data, philo->index);
		thinking(philo->index);
	}
}	

int is_dead(t_philo *philo)
{
	int diff;

	diff = get_time() - philo->last_meal;
	if (diff > philo->data->tt_die)
	{
		printf("%d\n", diff);
		return (1);
	}
	return (0);
}

void *monitor(void *arg)
{
	int i;
	t_philo *philos;
	t_data *data;
	int *ret;

	ret = malloc(sizeof(int));
	*ret = 1;
	philos = (t_philo *)arg;
	data = philos->data;
	i = 0;
	while (1)
	{
		if (is_dead(philos + i))
		{
			printf("%ld - %s%d died%s\n", get_time(), RED, i, WHT);
			return ((void *)ret);
		}
		i++;
		if (i == data->count)
			i = 0;
	}
	*ret = 0;	
	return ((void *)ret);
}

void simulate(t_data *data, t_philo *philos, pthread_t *threads)
{
	pthread_t monitor_th;
	int i;
	int *ret;

	i = -1;
	while (++i < data->count)
		pthread_create(threads + i, NULL, routine, philos + i);
	pthread_create(&monitor_th, NULL, monitor, philos);
	pthread_join(monitor_th, (void **)&ret);
	if (!*ret)
		while (--i > -1)
			pthread_join(threads[i], NULL);
	cleanup(data, philos, threads, ret);
}

void cleanup(t_data *data, t_philo *philos, pthread_t *threads, int *ret)
{
	int i;

	i = -1;
	while (++i < data->count)
		pthread_mutex_destroy(data->forks + i);
	free(philos);
	free(data->forks);
	free(threads);
	free(ret);
}

int main(int ac, char **av)
{
	t_data data;
	t_philo *philos;
	pthread_t *threads;

	if (ac < 4)
		return (1);
	philos = init_data(av + 1, &data);
	threads = malloc(data.count * sizeof(pthread_t));
	simulate(&data, philos, threads);
	return (0);
}