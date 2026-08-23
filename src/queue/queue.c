/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 21:25:38 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/23 18:04:27 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include "codexion.h"

void	queue_add_request(t_codexion *data, t_request *request)
{
	data->queue.queue[data->queue.size] = request;
	data->queue.size++;
	if (data->queue.scheduler == EDF)
		queue_heapify_up(&data->queue);
}

static void	queue_fifo_move(t_codexion *data)
{
	uint32_t	i;

	i = 0;
	while ((i++) < data->queue.size)
		data->queue.queue[i - 1] = data->queue.queue[i];
	data->queue.queue[i] = NULL;
}

static void	queue_edf_move(t_codexion *data)
{
	data->queue.queue[0] = data->queue.queue[data->queue.size];
	data->queue.queue[data->queue.size] = NULL;
	queue_heapify_down(&data->queue);
}

void	queue_pop_request(t_codexion *data)
{
	if (data->queue.size == 0)
		return ;
	free(data->queue.queue[0]);
	data->queue.size--;
	if (data->queue.size == 0)
		data->queue.queue[0] = NULL;
	else if (data->queue.scheduler == EDF)
		queue_edf_move(data);
	else
		queue_fifo_move(data);
}
