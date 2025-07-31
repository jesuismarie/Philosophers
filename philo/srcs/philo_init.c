/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:24:49 by mnazarya          #+#    #+#             */
/*   Updated: 2023/06/09 13:57:37 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	forks_to_philo(t_main *table)
{
	int	i;

	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* table->philo_count);
	if (!table->forks)
		return (1);
	i = -1;
	while (++i < table->philo_count)
		pthread_mutex_init(&(table->forks[i]), NULL);
	i = -1;
	while (++i < table->philo_count)
	{
		table->philos[i].left = &(table->forks[i]);
		if (table->philo_count != 1)
		{
			if (i == table->philo_count - 1)
				table->philos[i].right = &(table->forks[0]);
			else
				table->philos[i].right = &(table->forks[i + 1]);
		}
		else
			table->philos[i].right = &(table->forks[0]);
	}
	return (0);
}

void	philo_init(t_main *table, char **argv)
{
	int	i;

	i = -1;
	table->is_died = 0;
	pthread_mutex_init(&(table->mutex_die), NULL);
	pthread_mutex_init(&(table->mutex_write), NULL);
	while (++i < table->philo_count)
	{
		table->philos[i].time_to_die = table->time_to_die;
		table->philos[i].time_to_sleep = ft_atoi(argv[4]);
		table->philos[i].time_to_eat = ft_atoi(argv[3]);
		table->philos[i].is_died = &(table->is_died);
		table->philos[i].philo_id = i + 1;
		table->philos[i].eat_count = 0;
		table->philos[i].last_eat = table->start_time;
		table->philos[i].philo_count = table->philo_count;
		table->philos[i].mutex_die = &(table->mutex_die);
		table->philos[i].mutex_write = &(table->mutex_write);
		table->philos[i].start_time = &(table->start_time);
		pthread_mutex_init(&(table->philos[i].last_eat_mutex), NULL);
		pthread_mutex_init(&(table->philos[i].eat_count_mutex), NULL);
	}
}

int	args_init(t_main *table, int argc, char **argv)
{
	if (check_args(argc, argv))
	{
		printf ("Error\n");
		return (1);
	}
	table->philo_count = ft_atoi(argv[1]);
	if (table->philo_count <= 0 || ft_atoi(argv[4]) <= 0
		|| ft_atoi(argv[3]) <= 0)
		return (1);
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->philo_count);
	if (!table->philos)
		return (1);
	table->time_to_die = ft_atoi(argv[2]);
	if (forks_to_philo(table))
		return (1);
	philo_init(table, argv);
	table->eat_count = -1;
	if (argv[5])
		table->eat_count = ft_atoi(argv[5]);
	return (0);
}

unsigned long long	my_gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	my_usleep(t_philo *philo, unsigned long long t)
{
	unsigned long	time;

	time = my_gettime();
	while (!is_died(philo))
	{
		if (my_gettime() - time >= t)
			break ;
		usleep(50);
	}
}
