/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 18:04:41 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/19 15:25:37 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdint.h>
# include <stdbool.h>
# include <pthread.h>

typedef enum e_scheduler
{
	FIFO,
	EDF
}	t_scheduler;

typedef struct s_args
{
	uint32_t	coders_number;
	uint32_t	burnout_time;
	uint32_t	compile_time;
	uint32_t	debug_time;
	uint32_t	refactor_time;
	uint32_t	compiles_required;
	uint32_t	dongle_cooldown;
	t_scheduler	scheduler;

}	t_args;

typedef struct s_coder
{
	pthread_t		thread;
	uint32_t		number;
	uint32_t		compiles;
	t_args			*args;
	pthread_mutex_t	*first_dongle;
	pthread_mutex_t	*second_dongle;
}	t_coder;

typedef struct s_codexion
{
	t_args			*args;
	pthread_mutex_t	*dongles;
	t_coder			*coders;
}	t_codexion;

void	codexion(t_args *args);

void	*coder_routine(void *arg);

bool	init_codexion(t_codexion *data);

bool	parse_arguments(t_args *args, char **argv);

bool	is_valid_uint(char *str);

#endif
