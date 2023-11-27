/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:13:14 by dferjul           #+#    #+#             */
/*   Updated: 2023/11/23 20:08:47 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	ft_check_args(ac, av, data);
	ft_init_data(av, data);
	ft_init_philo(data);
	ft_start_philo(data);
	ft_free(data);
	return (0);
}
