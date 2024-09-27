/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:30:41 by lamhal            #+#    #+#             */
/*   Updated: 2024/09/25 17:22:43 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int				nbr_ph;
	int				tm_dth;
	int				tm_slp;
	int				tm_eat;
	int				nbr_to_eat;
	int				dead;
	pthread_mutex_t	*frk;
	pthread_mutex_t	prnt_mtx;
	pthread_mutex_t	dead_mtx;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				dead;
	int				start;
	int				tm_lst_meal;
	int				nbr_meals;
	pthread_t		thread;
	pthread_mutex_t	*frst_frk;
	pthread_mutex_t	*scnd_frk;
	pthread_mutex_t	mls_mtx;
	t_data			*data;
}	t_philo;

void	ft_putstr_fd(char *s, int fd);
int		parsing(int ac, char **av, int *input);
int		intailse_data(t_data *data, int *input, int ac);
int		intailse_philos(t_data *data, t_philo *philo);
int		get_current_time(void);
int		get_time_def(int time);
int		ft_usleep(size_t time, t_philo *philo);
int		ft_printf(t_philo *philo, int n);
int		philos(t_philo *philo);

#endif