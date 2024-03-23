/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayan <mayan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:56:27 by mayan             #+#    #+#             */
/*   Updated: 2024/03/21 21:49:51 by mayan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//./philo 5 800 200 200 [5]

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		if (parse_input(&data, av) == 0)
		{
			data_init(&data);
			start_sim(&data);
			clean(&data);
		}
	}
	else
	{
		error_exit("Error in Input: \n" G "try ./philo 5 800 200 200 [5]" RST);
	}
}
