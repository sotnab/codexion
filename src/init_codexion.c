/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_codexion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 14:17:53 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/22 19:34:03 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#include "codexion.h"

static void	init_dongles(t_codexion *data)
{
	uint32_t	i;

	i = 0;
	while (i < data->args->coders_number)
		pthread_mutex_init(data->dongles + (i++), NULL);
}

static void	init_coders(t_codexion *data)
{
	uint32_t	i;

	i = 0;
	while (i < data->args->coders_number)
	{
		data->coders[i].number = i + 1;
		data->coders[i].compiles = 0;
		data->coders[i].last_compile = 0;
		if (i + 1 < data->args->coders_number)
		{
			data->coders[i].first_dongle = i;
			data->coders[i].second_dongle = i + 1;
		}
		else
		{
			data->coders[i].first_dongle = 0;
			data->coders[i].second_dongle = i;
		}
		i++;
	}
}

static bool	init_queue(t_codexion *data)
{
	uint32_t	queue_size;

	queue_size = sizeof(t_request *) * data->args->coders_number;
	data->queue.scheduler = data->args->scheduler;
	data->queue.size = 0;
	data->queue.queue = malloc(queue_size);
	if (!data->queue.queue)
		return (false);
	memset(data->queue.queue, 0, queue_size);
	pthread_cond_init(&data->queue.cond, NULL);
	return (true);
}

static void	init_mutexes(t_codexion *data)
{
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->finish_lock, NULL);
	pthread_mutex_init(&data->queue_lock, NULL);
}

bool	init_codexion(t_codexion *data)
{
	data->finish = 0;
	data->dongles = malloc(sizeof(pthread_mutex_t) * data->args->coders_number);
	if (!data->dongles)
		return (false);
	init_dongles(data);
	data->coders = malloc(sizeof(t_coder) * data->args->coders_number);
	if (!data->coders)
		return (free(data->dongles), false);
	init_coders(data);
	init_queue(data);
	init_mutexes(data);
	return (true);
}
