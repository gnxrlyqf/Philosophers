#ifndef MAIN_H
# define MAIN_H

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>

# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"

typedef enum state
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD = -1
} t_state;

typedef struct s_data
{
	pthread_mutex_t *forks;
	int count;
	int tt_eat;
	int tt_sleep;
	int tt_die;
	int eat_min;
} t_data;

typedef struct s_philo
{
	int index;
	t_state state;
	int meal_count;
	int last_meal;
	t_data *data;	
} t_philo;

long	ft_atoi(char *str);
void	eating(t_data *data, int index);
void	sleeping(t_data *data, int index);

#endif