/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:47:19 by mnazarya          #+#    #+#             */
/*   Updated: 2023/06/15 20:47:12 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	line_print(t_philo *philo, char *s, unsigned long long t)
{
	sem_wait(philo->sem_print);
	printf("[%llu ms] %d %s\n", t, philo->philo_id, s);
	sem_post(philo->sem_print);
}
