/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 14:16:07 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/19 23:09:58 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include "codexion.h"

static void	print_coder_message(t_thread_arg *arg, t_message message)
{
	int			number;
	uint32_t	timestamp;

	if (arg->data->burned_out)
		return ;
	number = arg->coder->number;
	timestamp = get_cpu_ms();
	pthread_mutex_lock(&arg->data->print_lock);
	if (message == DONGLE)
		printf("%-6d %d has taken a dongle\n", timestamp, number);
	if (message == COMPILING)
		printf("%-6d %d is compiling\n", timestamp, number);
	if (message == DEBUGGING)
		printf("%-6d %d is debugging\n", timestamp, number);
	if (message == REFACTORING)
		printf("%-6d %d is refactoring\n", timestamp, number);
	pthread_mutex_unlock(&arg->data->print_lock);
}

void	coder_sleep(t_thread_arg *arg, uint32_t duration)
{
	uint32_t	finish;

	finish = get_cpu_ms() + duration;
	while (!arg->data->burned_out && get_cpu_ms() < finish)
		usleep(1000);
}

void	*coder_routine(void *arg)
{
	t_thread_arg	*thread_arg;

	thread_arg = (t_thread_arg *)arg;
	while (!thread_arg->data->burned_out)
	{
		pthread_mutex_lock(thread_arg->coder->first_dongle);
		print_coder_message(thread_arg, DONGLE);
		pthread_mutex_lock(thread_arg->coder->second_dongle);
		print_coder_message(thread_arg, DONGLE);
		print_coder_message(thread_arg, COMPILING);
		thread_arg->coder->last_compile = get_cpu_ms();
		coder_sleep(thread_arg, thread_arg->data->args->compile_time);
		pthread_mutex_unlock(thread_arg->coder->second_dongle);
		pthread_mutex_unlock(thread_arg->coder->first_dongle);
		print_coder_message(thread_arg, DEBUGGING);
		coder_sleep(thread_arg, thread_arg->data->args->debug_time);
		print_coder_message(thread_arg, REFACTORING);
		coder_sleep(thread_arg, thread_arg->data->args->refactor_time);
	}
	return (NULL);
}
