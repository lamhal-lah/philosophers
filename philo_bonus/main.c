/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:37:31 by lamhal            #+#    #+#             */
/*   Updated: 2024/09/26 15:38:42 by lamhal           ###   ########.fr       */
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
		return (ft_putstr_fd("invalide input\n", 2), 1);
	philo = malloc(sizeof(t_philo) * input[0]);
	if (!philo)
		return (ft_putstr_fd("failled malloc\n", 2), 1);
	if (intailse_data(&data, input, ac))
		return (1);
	if (intailse_philos(&data, philo))
		return (1);
	if (philos(philo))
		return (1);
}