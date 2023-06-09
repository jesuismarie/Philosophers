/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:24:38 by mnazarya          #+#    #+#             */
/*   Updated: 2023/06/09 15:41:41 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int					time_to_sleep;
	int					philo_count;
	int					time_to_eat;
	int					eat_count;
	int					*is_died;
	int					philo_id;
	unsigned long long	last_eat;
	pthread_t			philo;
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
	pthread_mutex_t		*mutex_die;
	pthread_mutex_t		*mutex_write;
	pthread_mutex_t		last_eat_mutex;
	pthread_mutex_t		eat_count_mutex;
}	t_philo;

typedef struct s_main
{
	unsigned long long	time_to_die;
	int					philo_count;
	int					eat_count;
	int					is_died;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		mutex_die;
	pthread_mutex_t		mutex_write;
}	t_main;

int					ft_atoi(const char *nptr);
int					check_args(int argc, char **argv);
int					forks_to_philo(t_main *table);
void				philo_init(t_main *table, char **argv);
int					args_init(t_main *table, int argc, char **argv);
unsigned long long	my_gettime(void);
void				my_usleep(t_philo *philo, unsigned long long t);
int					is_died(t_philo *philo);
void				*routine(void *info);
void				check_print(t_philo *philo, char *s, unsigned long long t);
int					check_die(t_main *table);
int					check_eat_count(t_main *table);
void				destroy_philo(t_main *table);

#endif
