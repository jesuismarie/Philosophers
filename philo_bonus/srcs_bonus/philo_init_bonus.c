/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:33:38 by mnazarya          #+#    #+#             */
/*   Updated: 2023/06/15 20:52:24 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	semaphore_init(t_philo *philo)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_DIE);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_EAT_COUNT);
	sem_unlink(SEM_LAST_EAT);
	philo->forks = sem_open(SEM_FORKS, O_CREAT, S_IRWXU, philo->philo_count);
	philo->sem_print = sem_open(SEM_PRINT, O_CREAT, S_IRWXU, 1);
	philo->sem_eat_count = sem_open(SEM_EAT_COUNT, O_CREAT, S_IRWXU, 1);
	philo->sem_last_eat = sem_open(SEM_LAST_EAT, O_CREAT, S_IRWXU, 1);
	if (philo->forks == SEM_FAILED || philo->sem_print == SEM_FAILED
		|| philo->sem_last_eat == SEM_FAILED
		|| philo->sem_eat_count == SEM_FAILED)
	{
		printf("Error");
		exit(1);
	}
}

void	philo_init(t_philo *philo, char **argv)
{
	philo->last_eat = 0;
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->eat_count = 0;
	philo->philo_count = ft_atoi(argv[1]);
	philo->is_died = 0;
}

int	args_init(t_main *table, char **argv)
{
	int		i;
	t_philo	philo;

	table->philo_count = ft_atoi(argv[1]);
	if (table->philo_count == 0)
		return (1);
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->philo_count);
	if (!table->philos)
		return (1);
	table->time_to_die = ft_atoi(argv[2]);
	table->eat_count = -1;
	if (argv[5])
		table->eat_count = ft_atoi(argv[5]);
	philo_init(&philo, argv);
	semaphore_init(&philo);
	i = -1;
	while (++i < table->philo_count)
	{
		table->philos[i] = philo;
		table->philos[i].philo_id = i + 1;
	}
	return (0);
}
