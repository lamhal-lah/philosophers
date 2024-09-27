/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 11:55:42 by lamhal            #+#    #+#             */
/*   Updated: 2024/09/26 19:00:44 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	intailse_data(t_data *data, int *input, int ac)
{
	data->nbr_ph = input[0];
	data->tm_dth = input[1];
	data->tm_eat = input[2];
	data->tm_slp = input[3];
	if (ac == 6)
		data->nbr_to_eat = input[4];
	else
		data->nbr_to_eat = -1;
	data->frk = malloc(sizeof(pthread_mutex_t) * input[0]);
	data->prnt_sem = sem_open("prnt_sem", O_CREAT, 0644, 1);
	if (data->prnt_sem == SEM_FAILED)
		return (ft_putstr_fd("failled to intialse mutex\n", 2), 1);
	data->dead_sem = sem_open("dead_sem", O_CREAT, 0644, 1);
	if (data->dead_sem == SEM_FAILED)
		return (ft_putstr_fd("failled to intialse mutex\n", 2), 1);
	data->dead = 0;
	free(input);
	return (0);
}

int	intailse_philos(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->nbr_ph)
	{
		philo[i].id = i + 1;
		philo[i].frst_frk = &data->frk[i];
		philo[i].nbr_meals = data->nbr_to_eat;
		philo[i].frst_frk = sem_open("frs_frk", O_CREAT, 0644, 1);
		if (philo[i].frst_frk == SEM_FAILED)
			return (ft_putstr_fd("failled to intialse mutex\n", 2), 1);
		philo[i].mls_sem = sem_open("mls_sem", O_CREAT, 0644, 1);
		if (philo[i].mls_sem == SEM_FAILED)
			return (ft_putstr_fd("failled to intialse mutex\n", 2), 1);
		philo[i].scnd_frk = &data->frk[(i + 1) % data->nbr_ph];
		philo[i].data = data;
	}
	return (0);
}
