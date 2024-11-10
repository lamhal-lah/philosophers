/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:29:48 by lamhal            #+#    #+#             */
/*   Updated: 2024/11/10 18:03:34 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	int		*input;
	t_data	data;
	t_philo	*philo;

	input = malloc((ac - 1) * sizeof(int));
	if (!input)
		return (ft_putstr_fd("falled malloc\n", 2), 1);
	if (parsing(ac, av, input))
		return (free(input), ft_putstr_fd("invalide input\n", 2), 1);
	if (intailse_data(&data, input, ac))
		return (1);
	philo = malloc(sizeof(t_philo) * input[0]);
	if (!philo)
		return (pthread_mutex_destroy(&data.prnt_mtx),
			pthread_mutex_destroy(&data.dead_mtx),
			ft_putstr_fd("falled malloc\n", 2), 1);
	if (intailse_philos(&data, philo))
		return (free(philo), pthread_mutex_destroy(&data.prnt_mtx),
			pthread_mutex_destroy(&data.dead_mtx), free(data.frk), 1);
	philos(philo);
	ft_destroy(philo, philo->data->nbr_ph, 1);
	return (free(philo), pthread_mutex_destroy(&data.prnt_mtx),
		pthread_mutex_destroy(&data.dead_mtx), free(data.frk), 0);
}
