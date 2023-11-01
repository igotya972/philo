/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:09:58 by dferjul           #+#    #+#             */
/*   Updated: 2023/10/31 19:44:54 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	ft_atoi(const char *str)
{
	int	i;
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

void	ft_init_data(int ac, char **av, t_data *data)
{
	data->nb_must_eat = 0;
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	//data->start_time = ft_times();
	data->end = 0;
	if (ac == 6)
		data->nb_must_eat = ft_atoi(av[5]);
	else
		data->nb_must_eat = 50000;
	if(pthread_mutex_init(&data->mutex, NULL) != 0)
		ft_error(data, "mutex init fail");
}

void	ft_init_philo(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * (data->nb_philo));
	if (!data->philos)
		ft_error(data, "init philo");
	i = -1;
	while (++i < data->nb_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].count_p_eat = 0;
		data->philos[i].data = data;
		if(pthread_mutex_init(&data->philos[i].fork, NULL) != 0)
			ft_error(data, "mutex init fail");
		data->philos[i].last_eat = ft_times();
		//printf("%lu\n", data->philos[i].last_eat);
	}
}
