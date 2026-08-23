/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 14:16:07 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/22 21:06:04 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include "codexion.h"

static void	coder_sleep(t_codexion *data, uint32_t duration)
{
	uint32_t	finish;

	finish = get_cpu_ms() + duration;
	while (!data->finish && get_cpu_ms() < finish)
		usleep(1000);
}

static void	print_coder_message(t_codexion *data, int number, t_message message)
{
	uint32_t	timestamp;

	timestamp = get_cpu_ms();
	pthread_mutex_lock(&data->print_lock);
	if (data->finish)
		return ((void)pthread_mutex_unlock(&data->print_lock));
	if (message == DONGLE)
		printf("%-6d %d has taken a dongle\n", timestamp, number);
	if (message == COMPILING)
		printf("%-6d %d is compiling\n", timestamp, number);
	if (message == DEBUGGING)
		printf("%-6d %d is debugging\n", timestamp, number);
	if (message == REFACTORING)
		printf("%-6d %d is refactoring\n", timestamp, number);
	pthread_mutex_unlock(&data->print_lock);
}

static void	get_dongle(t_codexion *data, t_coder *coder, uint32_t index)
{
	uint32_t	time;

	dongle_request(data, coder, index);
	time = get_cpu_ms();
	if (time < data->dongles[index].available_at)
		coder_sleep(data, data->dongles[index].available_at - time);
	print_coder_message(data, coder->number, DONGLE);
}

static void	put_down_dongle(t_codexion *data, uint32_t index)
{
	t_dongle	*dongle;

	dongle = &data->dongles[index];
	pthread_mutex_unlock(&dongle->mutex);
	dongle->available_at = get_cpu_ms() + data->args->dongle_cooldown;
}

void	*coder_routine(void *arg)
{
	t_codexion	*data;
	t_coder		*coder;

	data = (t_codexion *)((void **)arg)[0];
	coder = (t_coder *)((void **)arg)[1];
	while (!data->finish)
	{
		get_dongle(data, coder, coder->first_dongle);
		get_dongle(data, coder, coder->second_dongle);
		print_coder_message(data, coder->number, COMPILING);
		coder->last_compile = get_cpu_ms();
		coder_sleep(data, data->args->compile_time);
		put_down_dongle(data, coder->second_dongle);
		put_down_dongle(data, coder->first_dongle);
		coder->compiles++;
		print_coder_message(data, coder->number, DEBUGGING);
		coder_sleep(data, data->args->debug_time);
		print_coder_message(data, coder->number, REFACTORING);
		coder_sleep(data, data->args->refactor_time);
	}
	return (free(arg), NULL);
}
