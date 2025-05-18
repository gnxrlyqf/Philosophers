#include <main.h>

void take_forks(t_data *data, int left, int right, int index)
{
	if ((data->forks + right)->__data.__lock)
	{
		pthread_mutex_lock(data->forks + left);
		printf("%ld - %s%d has taken a fork%s\n", get_time(), BLU, index, WHT);
		pthread_mutex_lock(data->forks + right);
		printf("%ld - %s%d has taken a fork%s\n", get_time(), BLU, index, WHT);
	}
	else
	{
		pthread_mutex_lock(data->forks + right);
		printf("%ld - %s%d has taken a fork%s\n", get_time(), BLU, index, WHT);
		pthread_mutex_lock(data->forks + left);
		printf("%ld - %s%d has taken a fork%s\n", get_time(), BLU, index, WHT);		
	}
}

void eating(t_philo *philo)
{
	int left;
	int right;
	t_data *data;

	data = philo->data;
	left = philo->index;
	right = (philo->index + 1) * (philo->index != data->count - 1);
	take_forks(data, left, right, philo->index);
	printf("%ld - %s%d is eating%s\n", get_time(), YEL, philo->index, WHT);
	usleep(data->tt_eat * 1000);
	philo->last_meal = get_time();
	pthread_mutex_unlock(data->forks + left);
	pthread_mutex_unlock(data->forks + right);
}

void sleeping(t_data *data, int index)
{
	printf("%ld - %s%d is sleeping%s\n", get_time(), MAG, index, WHT);
	usleep(data->tt_sleep * 1000);
}

void	thinking(int index)
{
	printf("%ld - %s%d is thinking%s\n", get_time(), GRN, index, WHT);
}