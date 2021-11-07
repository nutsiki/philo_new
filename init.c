#include "philo.h"

int	check_args(char **s)
{
	int	i;
	int	j;

	i = 1;
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			if (s[i][j] < '0' || s[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void init_philo_fork(t_philo *philo, int i)
{
	if (i == 0)
		philo->forks_left = &philo->scene->forks[philo->scene->nb_philo - 1];
	else
		philo->forks_left = &philo->scene->forks[i - 1];
	philo->forks_right = &philo->scene->forks[i];
	return ;
}
int init_prephilo(t_scene *scene)
{
	int i;

	i = 0;
	scene->philo = (t_philo *)malloc(sizeof(t_philo) * scene->nb_philo);
	if (!scene->philo)
		return (-1);
	while (i < scene->nb_philo)
	{
		scene->philo[i].scene = scene;
		scene->philo[i].time_has_fork = 0;
		scene->philo[i].time_is_eating = 0;
		scene->philo[i].time_is_sleeping = 0;
		scene->philo[i].time_is_thinking = 0;
		scene->philo[i].time_is_dead = 0;
		scene->philo[i].is_eating = 0;
		scene->philo[i].nb_eat = 0;
		scene->philo[i].index = i + 1;
		scene->philo[i].last_eat = scene->start;
		scene->philo[i].new_eat = scene->start;
		init_philo_fork(&scene->philo[i], i);
		i++;
	}
	return (0);
}

t_scene *init_philo(t_scene *scene)
{
	int i;

	i = 0;
	scene->print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(scene->print, NULL);
	scene->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * scene->nb_philo);
	while (i < scene->nb_philo)
	{
		pthread_mutex_init(&scene->forks[i], NULL);
		i++;
	}
	if (init_prephilo(scene))
		return (NULL);
	return (scene);
}

t_scene *init(int argc, char **argv)
{
	t_scene *scene;

	if (check_args(argv))
		return (NULL);
	scene = (t_scene *)malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
//	scene->start = get_time();
	scene->start_process = 0;
	scene->nb_philo = ft_atoi(argv[1]);
	scene->time_to_die = ft_atoi(argv[2]);
	scene->time_to_eat = ft_atoi(argv[3]);
	scene->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		scene->nb_eat_max = ft_atoi(argv[5]);
	else
		scene->nb_eat_max = -1;
	scene = init_philo(scene);
	if (!scene)
		return (NULL);
	return (scene);
}