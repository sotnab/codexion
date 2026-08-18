/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 18:04:41 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/18 23:37:47 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>

typedef enum e_scheduler
{
	FIFO,
	EDF
}	t_scheduler;

typedef struct s_codexion
{
	unsigned int	coders_number;
	unsigned int	burnout_time;
	unsigned int	compile_time;
	unsigned int	debug_time;
	unsigned int	refactor_time;
	unsigned int	compiles_required;
	unsigned int	dongle_cooldown;
	t_scheduler		scheduler;

}	t_codexion;

typedef struct s_coder
{
	pthread_t		thread;
	unsigned int	number;
	t_codexion		*codexion;
	pthread_mutex_t	*first_dongle;
	pthread_mutex_t	*second_dongle;
}	t_coder;

void	codexion(t_codexion *data);

int		parse_arguments(t_codexion *data, char **argv);

int		is_valid_uint(char *str);

#endif
