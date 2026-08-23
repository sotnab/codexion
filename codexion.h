/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 18:04:41 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/23 13:35:16 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdint.h>
# include <stdbool.h>
# include <pthread.h>
# include <time.h>

typedef struct timespec	t_timespec;

typedef enum e_scheduler
{
	FIFO,
	EDF
}	t_scheduler;

typedef enum e_message
{
	DONGLE,
	COMPILING,
	DEBUGGING,
	REFACTORING
}	t_message;

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
	pthread_t	thread;
	uint32_t	number;
	uint32_t	compiles;
	uint32_t	last_compile;
	uint32_t	first_dongle;
	uint32_t	second_dongle;
}	t_coder;

typedef struct s_request
{
	uint32_t	number;
	uint32_t	dongle_index;
	uint32_t	deadline;
}	t_request;

typedef struct s_queue
{
	t_scheduler		scheduler;
	t_request		**queue;
	uint32_t		size;
	pthread_cond_t	cond;
}	t_queue;

typedef struct s_dongle
{
	pthread_mutex_t	mutex;
	uint32_t		available_at;
}	t_dongle;

typedef struct s_codexion
{
	t_args			*args;
	t_coder			*coders;
	t_queue			queue;
	t_dongle		*dongles;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	finish_lock;
	pthread_mutex_t	queue_lock;
	pthread_t		monitor;
	bool			finish;
}	t_codexion;

void		codexion(t_args *args);

void		run_threads(t_codexion *data);

void		join_threads(t_codexion *data);

void		*coder_routine(void *arg);

void		*monitor_routine(void *arg);

void		cleanup_codexion(t_codexion *data);

bool		init_codexion(t_codexion *data, t_args *args);

bool		parse_arguments(t_args *args, char **argv);

bool		is_valid_uint(char *str);

void		destroy_dongle_mutexes(t_codexion *data, uint32_t n);

bool		init_dongles(t_codexion *data);

bool		init_mutexes(t_codexion *data);

bool		init_queue(t_codexion *data);

bool		init_coders(t_codexion *data);

uint32_t	get_cpu_ms(void);

void		queue_add_request(t_codexion *data, t_request *request);

void		queue_pop_request(t_codexion *data);

void		queue_heapify_up(t_codexion *data);

void		queue_heapify_down(t_codexion *data);

void		dongle_request(t_codexion *data, t_coder *coder, uint32_t index);

#endif
