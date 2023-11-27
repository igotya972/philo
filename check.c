/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 20:06:10 by dferjul           #+#    #+#             */
/*   Updated: 2023/11/23 20:06:10 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_check_args(int ac, char **av, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	if (ac > 6 || ac < 5)
		ft_error(data, "ARGS");
	while (av[++i])
	{
		if (!av[i][0])
		{
			ft_error(data, "ARGS NULL");
		}
		j = -1;
		while (av[i][++j])
			if (av[i][j] < '0' || av[i][j] > '9')
				ft_error(data, "invalid nb");
	}
	if (av[1][0] < '1')
		ft_error(data, "invalid nb philo");
}

int	ft_check_death(t_data *data, int i)
{
	if (ft_times() - data->philos[i].last_eat >= data->time_to_die)
	{
		data->end = 1;
		printf("%lu %d %s\n",
			ft_times() - data->start_time[0], data->philos[i].id, "died");
		return (1);
	}
	return (0);
}

void	ft_supervise(t_data *data)
{
	int	i;

	while (1)
	{
		i = -1;
		pthread_mutex_lock(&data->mutex);
		while (++i < data->nb_philo)
		{
			if (ft_satiate(data, i) || ft_check_death(data, i))
			{
				pthread_mutex_unlock(&data->mutex);
				return ;
			}
		}
		pthread_mutex_unlock(&data->mutex);
	}
}
