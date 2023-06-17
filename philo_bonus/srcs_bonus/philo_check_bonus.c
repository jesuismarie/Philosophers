/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:56:18 by mnazarya          #+#    #+#             */
/*   Updated: 2023/06/17 16:23:03 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	*call_threads(void *info)
{
	t_data	*data;

	data = (t_data *)info;
	while (1)
	{
		sem_wait(data->philo_data->sem_last_eat);
		if ((my_gettime() - data->philo_data->last_eat)
			> data->table->time_to_die)
		{
			line_print(data->philo_data, "died", my_gettime());
			sem_wait(data->philo_data->sem_print);
			sem_post(data->philo_data->sem_last_eat);
			exit(1);
		}
		sem_post(data->philo_data->sem_last_eat);
		sem_wait(data->philo_data->sem_eat_count);
		if (data->table->eat_count != -1
			&& data->philo_data->eat_count >= data->table->eat_count)
		{
			sem_post(data->philo_data->sem_eat_count);
			exit (0);
		}
		sem_post(data->philo_data->sem_eat_count);
	}
	return (0);
}
