/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:25:37 by mnazarya          #+#    #+#             */
/*   Updated: 2023/06/08 22:47:42 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	is_died(t_philo *philo)
{
	int	n;

	pthread_mutex_lock(philo->mutex_die);
	n = *(philo->is_died);
	pthread_mutex_unlock(philo->mutex_die);
	return (n);
}

void	*check_die(void *data)
{
	int		i;
	t_main	*table;

	table = (t_main *)data;
	while (1)
	{
		i = -1;
		usleep(500);
		while (++i < table->philo_count)
		{
			pthread_mutex_lock(&(table->philos[i].last_eat_mutex));
			if ((my_gettime() - table->philos[i].last_eat) > table->time_to_die)
			{
				pthread_mutex_unlock(&(table->philos[i].last_eat_mutex));
				pthread_mutex_lock(&(table->mutex_die));
				table->is_died = 1;
				pthread_mutex_unlock(&(table->mutex_die));
				pthread_mutex_lock(&(table->mutex_write));
				printf("[%llu ms] %d %s\n", my_gettime() - table->start_time, (i + 1), "died");
				pthread_mutex_unlock(&(table->mutex_write));
				return (NULL);
			}
			pthread_mutex_unlock(&(table->philos[i].last_eat_mutex));
		}
	}
	return (NULL);
}

void	*check_eat_count(void *data)
{
	t_main	*table;
	int		i;
	int		count;

	table = (t_main *)data;
	while (1)
	{
		i = -1;
		count = 0;
		while (table->eat_count != -1 && ++i < table->philo_count)
		{
			pthread_mutex_lock(&(table->philos[i].eat_count_mutex));
			if (table->philos[i].eat_count >= table->eat_count)
				count++;
			pthread_mutex_unlock(&(table->philos[i].eat_count_mutex));
		}
		if (count == table->philo_count)
		{
			pthread_mutex_lock(&(table->mutex_full));
			table->is_full = 1;
			pthread_mutex_unlock(&(table->mutex_full));
			pthread_mutex_lock(&(table->mutex_die));
			table->is_died = 1;
			pthread_mutex_unlock(&(table->mutex_die));
			pthread_mutex_lock(&(table->mutex_write));
			printf("All philosophers have eaten %d times\n", table->eat_count);
			pthread_mutex_unlock(&(table->mutex_write));
			return (NULL);
		}
	}
	return (NULL);
}

void	check_print(t_philo *philo, char *s, unsigned long long t)
{
	pthread_mutex_lock(philo->mutex_write);
	if (!is_died(philo))
		printf("[%llu ms] %d %s\n", t - *(philo->start_time), philo->philo_id, s);
	pthread_mutex_unlock(philo->mutex_write);
}
