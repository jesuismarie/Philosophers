/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:24:27 by mnazarya          #+#    #+#             */
/*   Updated: 2023/06/09 13:29:28 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int argc, char **argv)
{
	t_main	table;
	int		i;

	if (args_init(&table, argc, argv))
		return (1);
	i = -1;
	my_gettime();
	while (++i < table.philo_count)
	{
		pthread_create(&(table.philos[i].philo), NULL, &routine,
			(void *)&(table.philos[i]));
	}
	while (1)
		if (check_die(&table) || check_eat_count(&table))
			break ;
	i = -1;
	while (++i < table.philo_count && table.philo_count != 1)
		pthread_join(table.philos[i].philo, NULL);
	destroy_philo(&table);
	return (0);
}
