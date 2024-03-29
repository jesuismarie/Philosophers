/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:01:40 by mnazarya          #+#    #+#             */
/*   Updated: 2023/06/15 20:48:22 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

int	main(int argc, char **argv)
{
	t_main	table;

	if (check_args(argc, argv) || args_init(&table, argv))
	{
		printf ("Error\n");
		return (1);
	}
	my_gettime();
	create_philo(&table);
	return (0);
}
