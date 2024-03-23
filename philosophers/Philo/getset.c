/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayan <mayan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:24:23 by mayan             #+#    #+#             */
/*   Updated: 2024/03/20 21:52:27 by mayan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	getlong(t_mtx *mutex, long *src)
{
	long	rtrn;

	safemtx(mutex, LOCK);
	rtrn = *src;
	safemtx(mutex, UNLOCK);
	return (rtrn);
}

void	setlong(t_mtx *mutex, long *dest, long value)
{
	safemtx(mutex, LOCK);
	*dest = value;
	safemtx(mutex, UNLOCK);
}

void	setbool(t_mtx *mutex, bool *dest, bool value)
{
	safemtx(mutex, LOCK);
	*dest = value;
	safemtx(mutex, UNLOCK);
}

bool	getbool(t_mtx *mutex, bool *src)
{
	bool	rtrn;

	safemtx(mutex, LOCK);
	rtrn = *src;
	safemtx(mutex, UNLOCK);
	return (rtrn);
}
