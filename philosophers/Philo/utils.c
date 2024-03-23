/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayan <mayan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 18:44:35 by mayan             #+#    #+#             */
/*   Updated: 2024/03/23 15:01:27 by mayan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safemlloc(size_t bytes)
{
	void	*rtrn;

	rtrn = malloc(bytes);
	if (rtrn == NULL)
		error_exit("Malloc error");
	return (rtrn);
}

void	safemtx(t_mtx *mutex, t_mtcode mtcode)
{
	if (INIT == mtcode)
		pthread_mutex_init(mutex, NULL);
	else if (DESTROY == mtcode)
		pthread_mutex_destroy(mutex);
	else if (LOCK == mtcode)
		pthread_mutex_lock(mutex);
	else if (UNLOCK == mtcode)
		pthread_mutex_unlock(mutex);
	else
		error_exit("wrong mutex code");
}

void	safethrd(pthread_t *thread, void *(*foo)(void *), void *arg,
		t_mtcode mtcode)
{
	if (CREATE == mtcode)
		pthread_create(thread, NULL, foo, arg);
	else if (JOIN == mtcode)
		pthread_join(*thread, NULL);
	else if (DETACH == mtcode)
		pthread_detach(*thread);
	else
		error_exit("wrong thread code");
}

long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

// Get start time
// Initialize current	time
// Check for simulation end
// Update current time
// Busy waiting with smaller sleep duration
// You can adjust the usleep value for finer control (e.g., 50)
// void	ft_usleep(long time, t_data *data)
// {
// 	long	start;
// 	long	elapsed;
// 	long	rem;

// 	start = get_current_time();
// 	while (get_current_time() - start < time)
// 	{
// 		if (getbool(&data->data_mtx, &data->deadphil) == true)
// 			break ;
// 		elapsed = get_current_time() - start;
// 		rem = time - elapsed;
// 		if (rem > 10000)
// 			usleep(rem / 2);
// 		else
// 		{
// 			while (get_current_time() - start < time)
// 				;
// 		}
// 	}
// }
// void	ft_usleep(long time, t_data *data)
// {
// 	long long	start_time;
// 	long long	elapsed_time;
// 	long long	remaining_time;

// 	elapsed_time = 0;
// 	// Convert milliseconds to microseconds for calculations
// 	start_time = get_current_time() * 1000;
// 	while (elapsed_time < time * 1000)
// 	{
// 		// Check if simulation has finished
// 		if (getbool(&data->data_mtx, &data->deadphil) == true)
// 			return ;
// 		// Get elapsed time in microseconds
// 		elapsed_time = get_current_time() * 1000 - start_time;
// 		// Calculate remaining time in microseconds
// 		remaining_time = time * 1000 - elapsed_time;
// 		// Use smaller sleep duration for small remaining times
// 		if (remaining_time > 10000)
// 		{ // Adjust threshold as needed (10ms in this example)
// 			usleep(remaining_time / 2);
// 		}
// 		else
// 		{
// 			// Busy wait for remaining time (less accurate for very small times)
// 			while (get_current_time() * 1000 - start_time < time * 1000)
// 				;
// 		}
// 	}
// }

void	ft_usleep(long time, t_data *data)
{
	long	start;
	long	elapsed;

	start = get_current_time();
	elapsed = start;
	while (elapsed - start < time)
	{
		if (getbool(&data->data_mtx, &data->deadphil) == true)
			return ;
		elapsed = get_current_time();
		usleep(1000);
	}
}
