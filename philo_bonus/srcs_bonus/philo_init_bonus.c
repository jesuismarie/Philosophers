/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:33:38 by mnazarya          #+#    #+#             */
/*   Updated: 2023/06/11 18:55:55 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

int	semaphore_init()
{
	
}

int	args_init(t_main *philo, int argc, char **argv)
{
	if (check_args(argc, argv))
	{
		printf ("Error\n");
		return (1);
	}
	philo->philo_count = ft_atoi(argv[1]);
	if (philo->philo_count == 0)
		return (1);
	philo->philos = (t_data *)malloc(sizeof(t_data) * philo->philo_count);
	if (!philo->philos)
		return (1);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->eat_count = -1;
	if (argv[5])
		philo->eat_count = ft_atoi(argv[5]);
	return (0);
}
