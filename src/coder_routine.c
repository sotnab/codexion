/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 14:16:07 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/21 15:20:09 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include "codexion.h"

static void	print_coder_message(t_codexion *data, int number, t_message message)
{
	uint32_t	timestamp;

	if (data->finish)
		return ;
	timestamp = get_cpu_ms();
	pthread_mutex_lock(&data->print_lock);
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

void	coder_sleep(t_codexion *data, uint32_t duration)
{
	uint32_t	finish;

	finish = get_cpu_ms() + duration;
	while (!data->finish && get_cpu_ms() < finish)
		usleep(1000);
}

static bool	is_my_turn(t_codexion *data, t_coder *coder, uint32_t index)
{
	t_request	*first_request;
	bool		my_turn;

	pthread_mutex_lock(&data->queue_lock);
	first_request = data->queue.queue[0];
	my_turn = first_request->number == coder->number
		&& first_request->dongle_index == index;
	if (my_turn)
	{
		queue_pop_request(data);
		pthread_cond_broadcast(&data->queue.cond);
	}
	pthread_mutex_unlock(&data->queue_lock);
	return (my_turn);
}

void	dongle_request(t_codexion *data, t_coder *coder, uint32_t index)
{
	t_request	*request;

	request = malloc(sizeof(t_request));
	pthread_mutex_lock(&data->queue_lock);
	request->number = coder->number;
	request->dongle_index = index;
	request->deadline = coder->last_compile + data->args->burnout_time;
	queue_add_request(data, request);
	pthread_mutex_unlock(&data->queue_lock);
	pthread_cond_broadcast(&data->queue.cond);
	pthread_mutex_lock(&data->dongles[index]);
	while (!is_my_turn(data, coder, index) && !data->finish)
		pthread_cond_wait(&data->queue.cond, &data->dongles[index]);
	print_coder_message(data, coder->number, DONGLE);
}

void	*coder_routine(void *arg)
{
	t_codexion	*data;
	t_coder		*coder;

	data = (t_codexion *)((void **)arg)[0];
	coder = (t_coder *)((void **)arg)[1];
	while (!data->finish)
	{
		dongle_request(data, coder, coder->first_dongle);
		dongle_request(data, coder, coder->second_dongle);
		print_coder_message(data, coder->number, COMPILING);
		coder->last_compile = get_cpu_ms();
		coder_sleep(data, data->args->compile_time);
		pthread_mutex_unlock(&data->dongles[coder->second_dongle]);
		pthread_mutex_unlock(&data->dongles[coder->first_dongle]);
		coder->compiles++;
		print_coder_message(data, coder->number, DEBUGGING);
		coder_sleep(data, data->args->debug_time);
		print_coder_message(data, coder->number, REFACTORING);
		coder_sleep(data, data->args->refactor_time);
	}
	return (free(arg), NULL);
}
