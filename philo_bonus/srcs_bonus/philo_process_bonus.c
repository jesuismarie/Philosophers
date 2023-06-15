/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:28:04 by mnazarya          #+#    #+#             */
/*   Updated: 2023/06/15 20:55:35 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	day_activity(t_philo *philo)
{
	sem_wait(philo->forks);
	line_print(philo, "has taken a left fork", my_gettime());
	sem_wait(philo->forks);
	line_print(philo, "has taken a right fork", my_gettime());
	line_print(philo, "is eating", my_gettime());
	sem_wait(philo->sem_last_eat);
	philo->sem_last_eat = my_gettime();
	sem_post(philo->sem_last_eat);
	sem_wait(philo->sem_eat_count);
	philo->sem_eat_count++;
	sem_post(philo->sem_eat_count);
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void	call_thread(t_main *table, int i)
{
	t_data	data;

	data.philo_data = &(table->philos[i]);
	data.table = table;
	pthread_create(&(table->philos[i]), NULL, &day_activity,
		(void *)&(table->philos[i]));
	sem_wait(&(table->philos[i].sem_last_eat));
	table->philos[i].sem_last_eat = my_gettime();
	sem_post(&(table->philos[i].sem_last_eat));
	if (table->philos[i].philo_id % 2 == 0)
		usleep(1000);
	while (1)
	{
		day_activity(&(table->philos[i]));
	}
	pthread_join(table->philos[i].philo, NULL);
}

void	create_philo(t_main *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_count)
	{
		table->philos[i].pid = fork();
		if (table->philos[i].pid == -1)
			exit (1);
		else if (table->philos[i].pid == 0)
			call_thread(table, i);
	}
}
