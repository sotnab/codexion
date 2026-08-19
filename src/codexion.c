/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 18:04:34 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/19 22:59:35 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include "codexion.h"

static t_thread_arg	*create_thread_arg(t_codexion *data, t_coder *coder)
{
	t_thread_arg	*thread_arg;

	thread_arg = malloc(sizeof(t_thread_arg));
	if (!thread_arg)
		return (NULL);
	thread_arg->data = data;
	thread_arg->coder = coder;
	return (thread_arg);
}

static void	run_threads(t_codexion *data)
{
	uint32_t	i;

	pthread_create(&data->monitor, NULL, monitor_routine, data);
	i = 0;
	while (i < data->args->coders_number)
	{
		pthread_create(&data->coders[i].thread, NULL,
			coder_routine, create_thread_arg(data, data->coders + i));
		i++;
	}
}

static void	join_threads(t_codexion *data)
{
	uint32_t	i;

	i = 0;
	while (i < data->args->coders_number)
		pthread_join(data->coders[i++].thread, NULL);
	pthread_join(data->monitor, NULL);
}

// get_cpu_ms() initializes static start time
void	codexion(t_args *args)
{
	t_codexion		data;

	data.args = args;
	data.burned_out = 0;
	if (!init_codexion(&data))
		return ((void)fprintf(stderr, "Malloc failed.\n"));
	get_cpu_ms();
	run_threads(&data);
	join_threads(&data);
}
