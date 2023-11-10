/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:15:25 by dferjul           #+#    #+#             */
/*   Updated: 2023/11/09 18:49:34 by dferjul          ###   ########.fr       */
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
		free(data->philos);
		if (data->start_time)
			free(data->start_time);
		free(data);
	}
	if (data->nb_philo)
		pthread_mutex_destroy(&data->mutex);
}

void	ft_error(t_data *data, char *str)
{
	ft_free(data);
	printf("error %s\n", str);
	exit(EXIT_FAILURE);
}
