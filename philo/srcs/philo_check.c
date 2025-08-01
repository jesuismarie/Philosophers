/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:25:37 by mnazarya          #+#    #+#             */
/*   Updated: 2025/08/01 11:51:53 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	check_philosopher_death(t_main *table, int i)
{
	pthread_mutex_lock(&(table->philos[i].last_eat_mutex));
	if ((my_gettime() - table->philos[i].last_eat) > table->time_to_die)
	{
		pthread_mutex_unlock(&(table->philos[i].last_eat_mutex));
		pthread_mutex_lock(&(table->mutex_die));
		table->is_died = 1;
		pthread_mutex_unlock(&(table->mutex_die));
		pthread_mutex_lock(&(table->mutex_write));
		printf("[%llu ms] %d %s\n", my_gettime() - table->start_time,
			(i + 1), "died");
		pthread_mutex_unlock(&(table->mutex_write));
		return (1);
	}
	pthread_mutex_unlock(&(table->philos[i].last_eat_mutex));
	return (0);
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
		pthread_mutex_lock(&(table->mutex_die));
		if (table->is_died == 1 && table->philo_count != 1)
		{
			pthread_mutex_unlock(&(table->mutex_die));
			return (NULL);
		}
		pthread_mutex_unlock(&(table->mutex_die));
		while (++i < table->philo_count)
		{
			if (check_philosopher_death(table, i))
				return (NULL);
		}
	}
	return (NULL);
}

static int	count_philosophers_who_ate_enough(t_main *table)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (table->eat_count != -1 && ++i < table->philo_count)
	{
		pthread_mutex_lock(&(table->philos[i].eat_count_mutex));
		if (table->philos[i].eat_count >= table->eat_count)
			count++;
		pthread_mutex_unlock(&(table->philos[i].eat_count_mutex));
	}
	return (count);
}

static void	handle_all_philosophers_full(t_main *table)
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
}

void	*check_eat_count(void *data)
{
	t_main	*table;
	int		count;

	table = (t_main *)data;
	while (1)
	{
		pthread_mutex_lock(&(table->mutex_die));
		if (table->is_died)
		{
			pthread_mutex_unlock(&(table->mutex_die));
			return (NULL);
		}
		pthread_mutex_unlock(&(table->mutex_die));
		count = count_philosophers_who_ate_enough(table);
		if (count == table->philo_count)
		{
			handle_all_philosophers_full(table);
			return (NULL);
		}
	}
	return (NULL);
}
