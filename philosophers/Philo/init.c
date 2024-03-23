/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayan <mayan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:25:04 by mayan             #+#    #+#             */
/*   Updated: 2024/03/21 21:13:21 by mayan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//pos of philo in array == right fork/first fork == philo id - 1
static void	assignforks(t_philo *philo, t_fork *forks, int philopos)
{
	int	philo_nbr;

	philo_nbr = philo->data->num_philos;
	philo->firstfork = &forks[(philopos + 1) % philo_nbr];
	philo->secondfork = &forks[philopos];
	if (philo->id % 2 == 0)
	{
		philo->firstfork = &forks[philopos];
		philo->secondfork = &forks[(philopos + 1) % philo_nbr];
	}
}
//in case of even philo, swap the forks

static void	philo_init(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < data->num_philos)
	{
		philo = &data->philos[i];
		philo->id = i + 1;
		philo->meals = 0;
		philo->full = false;
		safemtx(&philo->philo_mtx, INIT);
		philo->data = data;
		assignforks(philo, data->forks, i);
		i++;
	}
}

void	data_init(t_data *data)
{
	int	i;

	i = 0;
	data->deadphil = false;
	data->all_threads_ready = false;
	data->runningthreads = 0;
	safemtx(&data->data_mtx, INIT);
	safemtx(&data->print_mtx, INIT);
	data->philos = safemlloc(sizeof(t_philo) * data->num_philos);
	data->forks = safemlloc(sizeof(t_fork) * data->num_philos);
	while (i < data->num_philos)
	{
		safemtx(&data->forks[i].fork, INIT);
		data->forks[i].id = i;
		i++;
	}
	philo_init(data);
}
