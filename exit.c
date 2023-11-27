/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:15:25 by dferjul           #+#    #+#             */
/*   Updated: 2023/11/12 20:03:50 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_data *data)
{
	int	i;

	i = -1;
	if (data && data->philos)
	{
		while (++i < data->nb_philo)
		{
			pthread_mutex_destroy(&data->philos[i].fork);
		}
		free(data->start_time);
		free(data->philos);
	}
	if (data->nb_philo)
	{
		pthread_mutex_destroy(&data->mutex);
		pthread_mutex_destroy(&data->mutex_print);
	}
	free(data);
}

void	ft_error(t_data *data, char *str)
{
	ft_free(data);
	printf("error %s\n", str);
	exit(EXIT_FAILURE);
}
