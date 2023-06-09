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

int	check_die(t_main *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_count)
	{
		pthread_mutex_lock(&(table->philos[i].last_eat_mutex));
		if ((my_gettime() - table->philos[i].last_eat) > table->time_to_die)
		{
			pthread_mutex_lock(&(table->mutex_die));
			table->is_died = 1;
			pthread_mutex_unlock(&(table->mutex_die));
			pthread_mutex_lock(&(table->mutex_write));
			printf("[%llu ms] %d %s\n", my_gettime(), (i + 1), "died");
			pthread_mutex_unlock(&(table->mutex_write));
			pthread_mutex_unlock(&(table->philos[i].last_eat_mutex));
			return (1);
		}
		pthread_mutex_unlock(&(table->philos[i].last_eat_mutex));
	}
	return (0);
}

int	check_eat_count(t_main *table)
{
	int	i;

	i = 0;
	while (table->eat_count != -1 && i < table->philo_count)
	{
		pthread_mutex_lock(&(table->philos[i].eat_count_mutex));
		if (table->philos[i].eat_count >= table->eat_count)
		{
			pthread_mutex_unlock(&(table->philos[i].eat_count_mutex));
			i++;
		}
		else
			break ;
	}
	pthread_mutex_unlock(&(table->philos[i].eat_count_mutex));
	if (i == table->philo_count)
	{
		pthread_mutex_lock(&(table->mutex_die));
		table->is_died = 1;
		pthread_mutex_unlock(&(table->mutex_die));
		return (1);
	}
	return (0);
}

void	check_print(t_philo *philo, char *s, unsigned long long t)
{
	pthread_mutex_lock(philo->mutex_write);
	if (!is_died(philo))
		printf("[%llu ms] %d %s\n", t, philo->philo_id, s);
	pthread_mutex_unlock(philo->mutex_write);
}
