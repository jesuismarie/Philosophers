/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:38:23 by mnazarya          #+#    #+#             */
/*   Updated: 2025/08/01 01:04:16 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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

int	is_died(t_philo *philo)
{
	int	n;

	pthread_mutex_lock(philo->mutex_die);
	n = *(philo->is_died);
	pthread_mutex_unlock(philo->mutex_die);
	return (n);
}

void	check_print(t_philo *philo, char *s, unsigned long long t)
{
	pthread_mutex_lock(philo->mutex_write);
	if (!is_died(philo))
		printf("[%llu ms] %d %s\n", t - *(philo->start_time),
			philo->philo_id, s);
	pthread_mutex_unlock(philo->mutex_write);
}

void	destroy_philo(t_main *table)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&(table->mutex_die));
	pthread_mutex_destroy(&(table->mutex_write));
	pthread_mutex_destroy(&(table->mutex_full));
	while (i < table->philo_count)
	{
		pthread_mutex_destroy(&(table->philos[i].last_eat_mutex));
		pthread_mutex_destroy(&(table->philos[i].eat_count_mutex));
		pthread_mutex_destroy(&(table->forks[i]));
		i++;
	}
	free(table->philos);
	free(table->forks);
}
