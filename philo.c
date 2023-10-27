/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:13:14 by dferjul           #+#    #+#             */
/*   Updated: 2023/10/27 03:22:49 by dferjul          ###   ########.fr       */
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

int main (int ac, char **av)
{
	t_data	*data;
	
	data = malloc(sizeof(t_data));
	ft_check_args(ac, av, data);
	ft_init_data(ac, av, data);
	ft_init_philo(data);
	ft_start_philo(data);
	printf("Coucou\n");
	ft_supervise(data);
	return (0);
}

// init data et init philo et init mutex