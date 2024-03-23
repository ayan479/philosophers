/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayan <mayan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:15:14 by mayan             #+#    #+#             */
/*   Updated: 2024/03/22 16:42:34 by mayan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_for_thrds(t_data *data)
{
	while (!getbool(&data->data_mtx, &data->all_threads_ready))
		;
}

void	increaselong(t_mtx *mtx, long *val)
{
	safemtx(mtx, LOCK);
	(*val)++;
	safemtx(mtx, UNLOCK);
}

void	syncphilo(t_philo *philo)
{
	if (philo->data->num_philos % 2 == 0)
	{
		if (philo->id % 2 == 0)
			ft_usleep(1000, philo->data);
	}
	else
	{
		if (philo->id % 2)
			thinking(philo, true);
	}
}

int	error_exit(const char *error)
{
	printf(R "🚨%s⚠️😱🚨 \n" RST, error);
	return (EXIT_FAILURE);
}

void	clean(t_data *data)
{
	t_philo	*philos;
	int		i;

	i = 0;
	while (i < data->num_philos)
	{
		philos = &data->philos[i];
		safemtx(&philos->philo_mtx, DESTROY);
		i++;
	}
	safemtx(&data->data_mtx, DESTROY);
	safemtx(&data->print_mtx, DESTROY);
	free(data->philos);
	free(data->forks);
}
