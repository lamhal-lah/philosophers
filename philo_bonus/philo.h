/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:10:32 by lamhal            #+#    #+#             */
/*   Updated: 2024/09/26 16:13:53 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <semaphore.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int		nbr_ph;
	int		tm_dth;
	int		tm_slp;
	int		tm_eat;
	int		nbr_to_eat;
	int		dead;
	sem_t	*frk;
	sem_t	prnt_sem;
	sem_t	dead_sem;
}					t_data;

typedef struct s_philo
{
	int		id;
	int		dead;
	int		start;
	int		tm_lst_meal;
	int		nbr_meals;
	sem_t	*frst_frk;
	sem_t	*scnd_frk;
	sem_t	mls_sem;
	t_data  *data;
}	t_philo;

#endif