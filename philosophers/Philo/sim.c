/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayan <mayan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:34:55 by mayan             #+#    #+#             */
/*   Updated: 2024/03/23 15:33:45 by mayan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*lonelyphil(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	wait_for_thrds(philo->data);
	setlong(&philo->philo_mtx, &philo->last_time_ate, get_current_time());
	increaselong(&philo->data->data_mtx, &philo->data->runningthreads);
	philoprint(TAKEFORK1, philo);
	while (getbool(&philo->data->data_mtx, &philo->data->deadphil) == false)
		usleep(200);
	return (NULL);
}

void	thinking(t_philo *philo, bool presim)
{
	long	ttt;
	long	tte;
	long	tts;

	tte = philo->data->tte;
	tts = philo->data->tts;
	if (!presim)
		philoprint(THINKING, philo);
	if (philo->data->num_philos % 2 == 0)
		return ;
	ttt = (tte * 2) - tts;
	if (ttt < 0)
		ttt = 0;
	ft_usleep(ttt * 0.42, philo->data);
}

static void	eat(t_philo *philo)
{
	safemtx(&philo->firstfork->fork, LOCK);
	philoprint(TAKEFORK1, philo);
	safemtx(&philo->secondfork->fork, LOCK);
	philoprint(TAKEFORK2, philo);
	setlong(&philo->philo_mtx, &philo->last_time_ate, get_current_time());
	philoprint(EATING, philo);
	ft_usleep(philo->data->tte, philo->data);
	philo->meals++;
	if (philo->data->meallimit > 0 && philo->meals == philo->data->meallimit)
		setbool(&philo->philo_mtx, &philo->full, true);
	safemtx(&philo->firstfork->fork, UNLOCK);
	safemtx(&philo->secondfork->fork, UNLOCK);
}

void	*dindinsim(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	wait_for_thrds(philo->data);
	setlong(&philo->philo_mtx, &philo->last_time_ate, get_current_time());
	increaselong(&philo->data->data_mtx, &philo->data->runningthreads);
	if ((philo->id - 1) % 2 == 0)
		ft_usleep(philo->data->tte, philo->data);
	while (!getbool(&philo->data->data_mtx, &philo->data->deadphil))
	{
		if (philo->full)
			break ;
		eat(philo);
		philoprint(SLEEPING, philo);
		ft_usleep(philo->data->tts, philo->data);
		thinking(philo, false);
	}
	return (NULL);
}

/*
 * If no meals, return to main and clean
 * If only one philo, create necessary thread
 * 1) Create all the philosophers
 * 2) Create another thread to search
 * 		for dead ones
 * 3) set time_start_simulation and
 * 		set true ready all, so they can start simulation
 * 4) Wait for all
 * 5) If we pass line 164 it means all philos are full
 * 		so set deadphilulation for monitor
 * 6) Wait for monitor as well. Then jump to clean in main
 *
 * If we join all threads it means they are all full,
 * so the simulation is finished, therefore we set the
 * deadphilulation ON
 *
 * Useful cause also monitor uses this boolean, can be
 * turned on
 * 	~by philos ending cause full
 * 	~by monitor cause a philo died
 * It's a "2 way" bool for threads communication 💡
*/

void	start_sim(t_data *data)
{
	int	i;

	i = 0;
	if (data->meallimit == 0)
		return ;
	else if (data->num_philos == 1)
		safethrd(&data->philos[0].thread_id, lonelyphil, &data->philos[0],
			CREATE);
	else
	{
		while (i < data->num_philos)
		{
			safethrd(&data->philos[i].thread_id, dindinsim, &data->philos[i],
				CREATE);
			i++;
		}
	}
	safethrd(&data->monitor, monitor_din, data, CREATE);
	data->start_sim = get_current_time();
	setbool(&data->data_mtx, &data->all_threads_ready, true);
	i = -1;
	while (++i < data->num_philos)
		safethrd(&data->philos[i].thread_id, NULL, NULL, JOIN);
	setbool(&data->data_mtx, &data->deadphil, true);
	safethrd(&data->monitor, NULL, NULL, JOIN);
}
