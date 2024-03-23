/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayan <mayan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:10:31 by mayan             #+#    #+#             */
/*   Updated: 2024/03/22 17:07:03 by mayan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philoprint(t_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = get_current_time() - philo->data->start_sim;
	if (philo->full)
		return ;
	safemtx(&philo->data->print_mtx, LOCK);
	if ((TAKEFORK1 == status || TAKEFORK2 == status)
		&& !getbool(&philo->data->data_mtx, &philo->data->deadphil))
		printf(M FORK RST, elapsed, philo->id);
	else if (EATING == status && !getbool(&philo->data->data_mtx,
			&philo->data->deadphil))
		printf(Y EAT RST, elapsed, philo->id);
	else if (SLEEPING == status && !getbool(&philo->data->data_mtx,
			&philo->data->deadphil))
		printf(W SLEEP RST, elapsed, philo->id);
	else if (THINKING == status && !getbool(&philo->data->data_mtx,
			&philo->data->deadphil))
		printf(G THINK RST, elapsed, philo->id);
	else if (DEAD == status)
		printf(R DEATH RST, elapsed, philo->id);
	safemtx(&philo->data->print_mtx, UNLOCK);
}

// void	philoprint(t_status status, t_philo *philo)
// {
// 	long	elapsed;

// 	elapsed = get_current_time() - philo->data->start_sim;
// 	if (philo->full)
// 		return ;
// 	safemtx(&philo->data->print_mtx, LOCK);
// 	if (TAKEFORK1 == status && !getbool(&philo->data->data_mtx,
// 			&philo->data->deadphil))
// 	{
// 		printf(W "%6ld " RST "%d has taken the 1° fork \t\t\t\tn°" B "["
// 				"%d ]\n" RST, elapsed, philo->id, philo->firstfork->id);
// 	}
// 	else if (TAKEFORK2 == status && !getbool(&philo->data->data_mtx,
// 				&philo->data->deadphil))
// 	{
// 		printf(W "%6ld " RST "%d has taken the 2° fork \t\t\t\tn°" B "["
// 				"%d ]\n" RST, elapsed, philo->id, philo->secondfork->id);
// 	}
// 	else if (EATING == status && !getbool(&philo->data->data_mtx,
// 				&philo->data->deadphil))
// 	{
// 		printf(W "%6ld " C "%d is eating \t\t\t" Y "[ %ld ]\n" RST, elapsed,
// 				philo->id, philo->meals);
// 	}
// 	else if (SLEEPING == status && !getbool(&philo->data->data_mtx,
// 				&philo->data->deadphil))
// 	{
// 		printf(W "%6ld " RST "%d is sleeping \n", elapsed, philo->id);
// 	}
// 	else if (THINKING == status && !getbool(&philo->data->data_mtx,
// 				&philo->data->deadphil))
// 	{
// 		printf(G "%6ld " RST "%d is thinking \n", elapsed, philo->id);
// 	}
// 	else if (DEAD == status && getbool(&philo->data->data_mtx,
// 				&philo->data->deadphil))
// 	{
// 		printf(R "\t\t %6ld %d died\n" RST, elapsed, philo->id);
// 	}
// 	safemtx(&philo->data->print_mtx, UNLOCK);
// }
