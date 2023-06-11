/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:53:03 by mnazarya          #+#    #+#             */
/*   Updated: 2023/06/11 18:56:26 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>

typedef struct s_data
{
	int					time_to_sleep;
	int					time_to_eat;
	int					philo_count;
	int					eat_count;
	int					is_died;
	pid_t				philo_id;
	unsigned long long	last_eat;
}	t_data;

typedef struct s_main
{
	unsigned long long	time_to_die;
	int					philo_count;
	int					eat_count;
	t_data				*philos;
	sem_t				*forks;
}	t_main;

typedef struct s_philo
{
	t_data	*philo_data;
	t_main	*table;
}	t_philo;


int	ft_atoi(const char *nptr);
int	check_args(int argc, char **argv);
int	args_init(t_main *table, int argc, char **argv);

#endif