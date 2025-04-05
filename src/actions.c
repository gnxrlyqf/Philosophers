#include <main.h>

void take_forks(t_data data, int index)
{
	pthread_mutex_lock(&data.forks[index]);
	pthread_mutex_lock(&data.forks[index + 1]);
}

void eating(t_data *data, int index)
{
	pthread_mutex_lock(data->forks + index);
	pthread_mutex_lock(data->forks + index + 1);
	usleep(data->tt_eat * 1000);
	pthread_mutex_unlock(data->forks + index);
	pthread_mutex_unlock(data->forks + index + 1);
}

void sleeping(t_data *data, int index)
{
	printf("%d is sleeping\n", index);
	usleep(data->tt_sleep * 1000);
	printf("%d is thinking\n", index);
}

