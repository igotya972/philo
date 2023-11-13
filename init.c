/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:09:58 by dferjul           #+#    #+#             */
/*   Updated: 2023/11/12 07:20:46 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	ft_atoi(const char *str)
{
	int				i;
	unsigned int	result;

	i = 0;
	result = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		result += (str[i] - 48);
		i++;
		if (!(str[i] < '0' || str[i] > '9'))
			result *= 10;
	}
	return (result);
}

int	ft_init_data(char **av, t_data *data)
{
	data->nb_must_eat = 0;
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->end = 0;
	data->nb_must_eat = -1;
	if (av[5])
	{
		data->nb_must_eat = ft_atoi(av[5]);
		if (data->nb_must_eat <= 0)
			return (1);
	}
	data->start_time = malloc(sizeof (unsigned long));
	if (!data->start_time)
		ft_error(data, "malloc start_time");
	data->start_time[0] = ft_times();
	if (pthread_mutex_init(&data->mutex, NULL) != 0)
		ft_error(data, "mutex init");
	if (pthread_mutex_init(&data->mutex_print, NULL) != 0)
		ft_error(data, "mutex_print init");
	return (0);
}

void	ft_init_philo(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * (data->nb_philo));
	if (!data->philos)
		ft_error(data, "malloc philo");
	i = -1;
	while (++i < data->nb_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].count_p_eat = 0;
		data->philos[i].data = data;
		if (pthread_mutex_init(&data->philos[i].fork, NULL) != 0)
			ft_error(data, "mutex_fork init");
		data->philos[i].last_eat = ft_times();
	}
}
