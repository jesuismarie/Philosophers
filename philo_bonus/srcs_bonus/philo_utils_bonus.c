/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:38:23 by mnazarya          #+#    #+#             */
/*   Updated: 2023/06/15 18:31:20 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

int	ft_atoi(const char *nptr)
{
	int	i;
	int	j;
	int	nb;

	i = 0;
	nb = 0;
	j = 1;
	while (nptr[i] == '\n' || nptr[i] == ' ' || nptr[i] == '\t'
		|| nptr[i] == '\f' || nptr[i] == '\v' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			j = -j;
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
		nb = (nb * 10) + (nptr[i++] - 48);
	return (nb * j);
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
		return (1);
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
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

void	my_usleep(t_philo *philo, unsigned long long t)
{
	unsigned long	time;

	time = my_gettime();
	// while (!is_died(philo))
	while (my_gettime() - time >= t)
	{
		// if (my_gettime() - time >= t)
		// 	break ;
		usleep(50);
	}
}

void	unlink_close(t_philo *philo)
{
	sem_close(philo->forks);
	sem_close(philo->sem_die);
	sem_close(philo->sem_print);
	sem_close(philo->sem_eat_count);
	sem_close(philo->sem_last_eat);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_DIE);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_EAT_COUNT);
	sem_unlink(SEM_LAST_EAT);
}
