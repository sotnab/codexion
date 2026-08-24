/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 19:34:36 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/24 19:35:53 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include "codexion.h"

void	print_coder_message(t_codexion *data, int number, t_message message)
{
	uint32_t	timestamp;

	timestamp = get_cpu_ms();
	pthread_mutex_lock(&data->print_lock);
	if (get_finish(data))
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

t_request	*create_request(
	t_codexion *data, t_coder *coder, uint32_t index)
{
	t_request	*request;

	request = malloc(sizeof(t_request));
	if (!request)
		return (NULL);
	request->number = coder->number;
	request->dongle_index = index;
	request->deadline = coder->last_compile + data->args->burnout_time;
	return (request);
}
