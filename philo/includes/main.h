/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchetoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:53:38 by mchetoui          #+#    #+#             */
/*   Updated: 2025/07/13 18:53:40 by mchetoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include <sys/time.h>
# include <string.h>

# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"

# define FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIE 4

typedef struct s_data
{
	pthread_mutex_t	*forks;
	long			start;
	int				count;
	int				tt_eat;
	int				tt_sleep;
	int				tt_die;
	int				eat_min;
	int				running;
	pthread_mutex_t monitor;
	pthread_mutex_t	run;
	pthread_mutex_t	print;
}	t_data;

typedef struct s_philo
{
	int		index;
	int		meal_count;
	int		last_meal;
	t_data	*data;
}	t_philo;

long	_atoi(char *str);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
long	get_time(void);
void	cleanup(t_data *data, t_philo *philos, pthread_t *threads, int *ret);
int		parse(char *av);
int		max(int a, int b);
void	_sleep(int time, t_data *data);
int		is_running(t_data *data);
void	print_action(t_data *data, int index, int action);
t_philo	*init_data(char **args, t_data *data);
void	simulate(t_data *data, t_philo *philos, pthread_t *threads);
void	*routine(void *arg);
int		simulation_over(t_philo *philos);
void	*single_thread(void *arg);

#endif