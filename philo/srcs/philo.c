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
	pthread_create(&table.die_checker, NULL, &check_die, (void *)&table);
	if (table.eat_count != -1)
		pthread_create(&table.eat_checker, NULL, &check_eat_count,
			(void *)&table);
	table.start_time = my_gettime();
	i = -1;
	while (++i < table.philo_count)
	{
		pthread_create(&(table.philos[i].philo), NULL, &routine,
			(void *)&(table.philos[i]));
	}
	i = -1;
	while (++i < table.philo_count)
		pthread_join(table.philos[i].philo, NULL);
	pthread_join(table.die_checker, NULL);
	if (table.eat_count != -1)
		pthread_join(table.eat_checker, NULL);
	destroy_philo(&table);
	return (0);
}
