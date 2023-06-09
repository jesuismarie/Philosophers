/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:38:12 by mnazarya          #+#    #+#             */
/*   Updated: 2023/06/09 13:57:48 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	pick_forks(t_philo *philo)
{
	if (philo->philo_id == philo->philo_count)
	{
		pthread_mutex_lock(philo->right);
		check_print(philo, "has taken a right fork", my_gettime());
		pthread_mutex_lock(philo->left);
		check_print(philo, "has taken a left fork", my_gettime());
	}
	else
	{
		pthread_mutex_lock(philo->left);
		check_print(philo, "has taken a left fork", my_gettime());
		pthread_mutex_lock(philo->right);
		check_print(philo, "has taken a right fork", my_gettime());
	}
}

static void	day_activity(t_philo *philo)
{
	while (!is_died(philo))
	{
		pick_forks(philo);
		check_print(philo, "is eating", my_gettime());
		pthread_mutex_lock(&(philo->last_eat_mutex));
		philo->last_eat = my_gettime();
		pthread_mutex_unlock(&(philo->last_eat_mutex));
		my_usleep(philo, philo->time_to_eat);
		pthread_mutex_lock(&(philo->eat_count_mutex));
		philo->eat_count++;
		pthread_mutex_unlock(&(philo->eat_count_mutex));
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		check_print(philo, "is sleeping", my_gettime());
		my_usleep(philo, philo->time_to_sleep);
		check_print(philo, "is thinking", my_gettime());
	}
}

void	*routine(void *info)
{
	t_philo	*philo;

	philo = (t_philo *)info;
	pthread_mutex_lock(&(philo->last_eat_mutex));
	philo->last_eat = my_gettime();
	pthread_mutex_unlock(&(philo->last_eat_mutex));
	if (philo->philo_id % 2 == 0)
		usleep(1000);
	day_activity(philo);
	return (0);
}
