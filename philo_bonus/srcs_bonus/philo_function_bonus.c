/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_function_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:47:19 by mnazarya          #+#    #+#             */
/*   Updated: 2023/06/17 17:34:36 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	line_print(t_philo *philo, char *s, unsigned long long t)
{
	sem_wait(philo->sem_print);
	printf("[%llu ms] %d %s\n", t, philo->philo_id, s);
	sem_post(philo->sem_print);
}

unsigned long long	my_gettime(void)
{
	static unsigned long long	start;
	struct timeval				time;
	static int					count;

	if (count == 0)
	{
		gettimeofday(&time, NULL);
		start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
		count++;
	}
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - start);
}

void	my_usleep(unsigned long long t)
{
	unsigned long	time;

	time = my_gettime();
	while (1)
	{
		if (my_gettime() - time >= t)
			break ;
		usleep(50);
	}
}
