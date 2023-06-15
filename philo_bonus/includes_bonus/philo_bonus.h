/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:53:03 by mnazarya          #+#    #+#             */
/*   Updated: 2023/06/15 20:47:27 by mnazarya         ###   ########.fr       */
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

# define SEM_FORKS "/sem_forks"
# define SEM_DIE "/sem_die"
# define SEM_PRINT "/sem_print"
# define SEM_EAT_COUNT "/sem_eat_count"
# define SEM_LAST_EAT "/sem_last_eat"

typedef struct s_philo
{
	unsigned long long	last_eat;
	int					time_to_sleep;
	int					time_to_eat;
	int					philo_count;
	int					eat_count;
	int					is_died;
	int					philo_id;
	pid_t				pid;
	sem_t				*forks;
	sem_t				*sem_print;
	sem_t				*sem_eat_count;
	sem_t				*sem_last_eat;
	pthread_t			philo;
}	t_philo;

typedef struct s_main
{
	unsigned long long	time_to_die;
	int					philo_count;
	int					eat_count;
	t_philo				*philos;
}	t_main;

typedef struct s_data
{
	t_philo	*philo_data;
	t_main	*table;
}	t_data;

int					ft_atoi(const char *nptr);
int					check_args(int argc, char **argv);
void				semaphore_init(t_philo *philo);
void				philo_init(t_philo *philo, char **argv);
int					args_init(t_main *table, char **argv);
unsigned long long	my_gettime(void);
void				my_usleep(t_philo *philo, unsigned long long t);
void				line_print(t_philo *philo, char *s, unsigned long long t);
void				create_philo(t_main *table);
void				unlink_close(t_philo *philo);

#endif