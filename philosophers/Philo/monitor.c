/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayan <mayan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:42:30 by mayan             #+#    #+#             */
/*   Updated: 2024/03/21 16:27:14 by mayan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	all_threads_running(t_mtx *mtx, long *threads, long num_philos)
{
	bool	ret;

	ret = false;
	safemtx(mtx, LOCK);
	if (*threads == num_philos)
		ret = true;
	safemtx(mtx, UNLOCK);
	return (ret);
}

static bool	philodied(t_philo *philo)
{
	long	timeelapsed;

	if (getbool(&philo->philo_mtx, &philo->full))
		return (false);
	timeelapsed = get_current_time() - getlong(&philo->philo_mtx,
			&philo->last_time_ate);
	if (timeelapsed > philo->data->ttd)
		return (true);
	return (false);
}

void	*monitor_din(void *ptr)
{
	int		i;
	t_data	*data;

	data = (t_data *)ptr;
	while (!all_threads_running(&data->data_mtx, &data->runningthreads,
			data->num_philos))
		;
	while (!getbool(&data->data_mtx, &data->deadphil))
	{
		i = 0;
		while (i < data->num_philos && !getbool(&data->data_mtx,
				&data->deadphil))
		{
			if (philodied(&data->philos[i]))
			{
				setbool(&data->data_mtx, &data->deadphil, true);
				philoprint(DEAD, &data->philos[i]);
			}
			i++;
		}
	}
	return (NULL);
}
