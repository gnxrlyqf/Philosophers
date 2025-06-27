#include <main.h>

void take_forks(t_data *data, int left, int right, int index)
{
	if (index % 2 == 0)
	{
		pthread_mutex_lock(data->forks + left);
		printf("%ld %s%d has taken a fork%s\n", get_time() - data->start, BLU, index, WHT);
		pthread_mutex_lock(data->forks + right);
		printf("%ld %s%d has taken a fork%s\n", get_time() - data->start, BLU, index, WHT);
	}
	else
	{
		pthread_mutex_lock(data->forks + right);
		printf("%ld %s%d has taken a fork%s\n", get_time() - data->start, BLU, index, WHT);
		pthread_mutex_lock(data->forks + left);
		printf("%ld %s%d has taken a fork%s\n", get_time() - data->start, BLU, index, WHT);		
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
	philo->last_meal = get_time();
	printf("%ld %s%d is eating%s\n", get_time() - data->start, YEL, philo->index, WHT);
	usleep(data->tt_eat * 1000);
	pthread_mutex_unlock(data->forks + left);
	pthread_mutex_unlock(data->forks + right);
	philo->meal_count++;
}

void sleeping(t_philo *philo)
{
	int time;

	if (philo->data->count % 2 == 0 || philo->index == philo->data->count - 1)
		time = philo->data->tt_sleep;
	else
		time = max((philo->data->tt_die - (get_time() - philo->last_meal)), philo->data->tt_sleep);
	printf("%ld %s%d is sleeping%s\n", get_time() - philo->data->start, MAG, philo->index, WHT);
	usleep(time * 1000);
}

void	thinking(t_philo *philo)
{
	printf("%ld %s%d is thinking%s\n", get_time() - philo->data->start, GRN, philo->index, WHT);
}