/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:38:23 by mnazarya          #+#    #+#             */
/*   Updated: 2023/06/17 13:42:29 by mnazarya         ###   ########.fr       */
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

static void	unlink_close(t_philo *philo)
{
	sem_close(philo->forks);
	sem_close(philo->sem_print);
	sem_close(philo->sem_eat_count);
	sem_close(philo->sem_last_eat);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_EAT_COUNT);
	sem_unlink(SEM_LAST_EAT);
}

void	kill_philos(t_main *table)
{
	int	i;
	int	status;

	i = -1;
	while (++i < table->philo_count)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) > 0)
		{
			i = -1;
			while (++i < table->philo_count)
				kill(table->philos[i].pid, SIGKILL);
			break ;
		}
	}
	unlink_close(table->philos);
	free(table->philos);
}
