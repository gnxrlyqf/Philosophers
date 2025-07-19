/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchetoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:38:03 by mchetoui          #+#    #+#             */
/*   Updated: 2025/07/13 18:38:04 by mchetoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

void	take_forks(t_data *data, int left, int right, int index)
{
	if (index % 2 == 0)
	{
		pthread_mutex_lock(data->forks + left);
		print_action(data, index, FORK);
		pthread_mutex_lock(data->forks + right);
		print_action(data, index, FORK);
	}
	else
	{
		pthread_mutex_lock(data->forks + right);
		print_action(data, index, FORK);
		pthread_mutex_lock(data->forks + left);
		print_action(data, index, FORK);
	}
}

void	eating(t_philo *philo)
{
	int		left;
	int		right;
	t_data	*data;

	data = philo->data;
	left = philo->index;
	right = (philo->index + 1) * (philo->index != data->count - 1);
	take_forks(data, left, right, philo->index);
	philo->last_meal = get_time();
	print_action(philo->data, philo->index, EAT);
	_sleep(data->tt_eat, data);
	pthread_mutex_unlock(data->forks + left);
	pthread_mutex_unlock(data->forks + right);
	philo->meal_count++;
}

void	sleeping(t_philo *philo)
{
	int	time;

	if (philo->data->count % 2 == 0)
		time = philo->data->tt_sleep;
	else
		time = max((philo->data->tt_die - (get_time() - philo->last_meal)),
				philo->data->tt_sleep);
	print_action(philo->data, philo->index, SLEEP);
	_sleep(time, philo->data);
}

void	thinking(t_philo *philo)
{
	print_action(philo->data, philo->index, THINK);
}

void	print_action(t_data *data, int index, int action)
{
	static char	*actions[] = {
		"%ld %s%d has taken a fork%s\n",
		"%ld %s%d is eating%s\n",
		"%ld %s%d is sleeping%s\n",
		"%ld %s%d is thinking%s\n",
	};
	static char	*color[] = {BLU, YEL, MAG, GRN};
	long		now;

	now = get_time() - data->start;
	pthread_mutex_lock(&data->print);
	if (is_running(data))
		printf(actions[action], now, color[action], index + 1, WHT);
	pthread_mutex_unlock(&data->print);
}
