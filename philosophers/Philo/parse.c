/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayan <mayan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:58:31 by mayan             #+#    #+#             */
/*   Updated: 2024/03/22 21:41:48 by mayan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_whitespace(int c)
{
	return (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v');
}

static const char	*valid_input(const char *str)
{
	int			len;
	const char	*num;

	len = 0;
	while (is_whitespace(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_exit("No negatives allowed");
	if (!(*str >= '0' && *str <= '9'))
		error_exit("Input is not digit");
	num = str;
	while (*str >= '0' && *str <= '9')
	{
		++len;
		if (len > 10)
			error_exit("Value too big");
		++str;
	}
	return (num);
}

static long	ft_atol(const char *str)
{
	long	val;

	val = 0;
	str = valid_input(str);
	while (*str >= '0' && *str <= '9')
	{
		val = (val * 10) + (*str++ - '0');
		if (val > INT_MAX)
			error_exit("Value too dang big (bigger than INT_MAX)");
	}
	return (val);
}

int	parse_input(t_data *data, char **av)
{
	data->num_philos = ft_atol(av[1]);
	if (data->num_philos > MAXPHILO)
	{
		printf("Max num of Philos are %d\n" RST, MAXPHILO);
		return (1);
	}
	data->ttd = ft_atol(av[2]);
	data->tte = ft_atol(av[3]);
	data->tts = ft_atol(av[4]);
	if (av[5])
		data->meallimit = ft_atol(av[5]);
	else
		data->meallimit = -1;
	return (0);
}
