/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 14:16:07 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/19 17:48:02 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include "codexion.h"

static void	print_coder_message(t_thread_arg *arg, t_message message)
{
	int			number;
	uint32_t	timestamp;

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

void	*coder_routine(void *arg)
{
	t_thread_arg	*thread_arg;

	thread_arg = (t_thread_arg *)arg;
	while (1)
	{
		pthread_mutex_lock(thread_arg->coder->first_dongle);
		print_coder_message(thread_arg, DONGLE);
		pthread_mutex_lock(thread_arg->coder->second_dongle);
		print_coder_message(thread_arg, DONGLE);
		print_coder_message(thread_arg, COMPILING);
		usleep(thread_arg->data->args->compile_time * 1000);
		pthread_mutex_unlock(thread_arg->coder->second_dongle);
		pthread_mutex_unlock(thread_arg->coder->first_dongle);
		print_coder_message(thread_arg, DEBUGGING);
		usleep(thread_arg->data->args->debug_time * 1000);
		print_coder_message(thread_arg, REFACTORING);
		usleep(thread_arg->data->args->refactor_time * 1000);
	}
	return (NULL);
}
