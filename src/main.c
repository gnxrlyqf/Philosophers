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

	data->count = parse(*args++);
	data->tt_die = parse(*args++);
	data->tt_eat = parse(*args++);
	data->tt_sleep = parse(*args++);
	if (data->count == -1 || data->tt_die == -1
		|| data->tt_eat == -1 || data->tt_sleep == -1)
		{
			write(2, "Invalid input\n", 16);
			return (NULL);
		}
	data->eat_min = -1;
	if (*args)
	{
		data->eat_min = parse(*args);
		if (data->eat_min == -1)
			return (NULL);
	}
	pthread_mutex_init(&data->run, NULL);
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

int is_running(t_data *data)
{
	int running;

	pthread_mutex_lock(&data->run);
	running = data->running;
	pthread_mutex_unlock(&data->run);
	return (running);
}

void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	philo->last_meal = get_time();
	if (philo->index % 2 != 0)
		usleep(200 + 1500 * (philo->index == philo->data->count - 1 && philo->data->count % 2));
	while (is_running(philo->data))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int is_dead(t_philo *philo)
{
	int diff;

	diff = get_time() - philo->last_meal;
	if (diff > philo->data->tt_die)
		return (1);
	return (0);
}

int simulation_over(t_philo *philos)
{
	int ate;
	int i;
	t_data *data;

	data = philos->data;
	ate = 0;
	i = -1;
	while (++i < data->count)
	{
		if (is_dead(philos + i))
		{
			printf("%ld - %s%d died%s\n", get_time() - data->start, RED, i, WHT);
			return (1);
		}
		if (data->eat_min != -1 && (*(philos + i)).meal_count == data->eat_min)
			ate++;
	}
	return (ate == data->count);
}

void *monitor(void *arg)
{
	t_philo *philos;
	t_data *data;

	philos = (t_philo *)arg;
	data = philos->data;
	while (1)
	{
		if (simulation_over(philos))
			break ;
		usleep(20);
	}
	return (NULL);
}

void simulate(t_data *data, t_philo *philos, pthread_t *threads)
{
	pthread_mutex_t running;
	pthread_t monitor_th;
	int i;
	int *ret;

	data->start = get_time();
	data->running = 1;
	i = -1;
	while (++i < data->count)
		pthread_create(threads + i, NULL, routine, philos + i);
	pthread_create(&monitor_th, NULL, monitor, philos);
	pthread_join(monitor_th, (void **)&ret);
	pthread_mutex_lock(&running);
	data->running = 0;
	pthread_mutex_unlock(&running);
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