/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 21:25:38 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/21 15:18:27 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include "codexion.h"

static void	request_swap(t_request **a, t_request **b)
{
	void	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static void	queue_edf_heapify(t_codexion *data)
{
	uint32_t	index;
	uint32_t	parent;
	t_request	**queue;

	if (data->queue.size < 2)
		return ;
	index = data->queue.size - 1;
	queue = data->queue.queue;
	while (index != 0)
	{
		parent = (index - 1) / 2;
		if (queue[index]->deadline >= queue[parent]->deadline)
			break ;
		request_swap(queue + index, queue + parent);
		index = parent;
	}
}

void	queue_add_request(t_codexion *data, t_request *request)
{
	data->queue.queue[data->queue.size] = request;
	data->queue.size++;
	if (data->queue.scheduler == EDF)
		queue_edf_heapify(data);
}

static void	queue_edf_heapify_down(t_codexion *data)
{
	uint32_t	index;
	uint32_t	left;
	uint32_t	right;
	uint32_t	smallest;
	t_request	**queue;

	queue = data->queue.queue;
	index = 0;
	while (1)
	{
		left = 2 * index + 1;
		right = 2 * index + 2;
		smallest = index;
		if (left < data->queue.size
			&& queue[left]->deadline < queue[smallest]->deadline)
			smallest = left;
		if (right < data->queue.size
			&& queue[right]->deadline < queue[smallest]->deadline)
			smallest = right;
		if (smallest == index)
			break ;
		request_swap(queue + index, queue + smallest);
		index = smallest;
	}
}

void	queue_pop_request(t_codexion *data)
{
	uint32_t	i;

	if (data->queue.size == 0)
		return ;
	free(data->queue.queue[0]);
	data->queue.size--;
	if (data->queue.size == 0)
	{
		data->queue.queue[0] = NULL;
		return ;
	}
	if (data->queue.scheduler == EDF)
	{
		data->queue.queue[0] = data->queue.queue[data->queue.size];
		data->queue.queue[data->queue.size] = NULL;
		queue_edf_heapify_down(data);
	}
	else
	{
		i = 0;
		while (i < data->queue.size)
		{
			data->queue.queue[i] = data->queue.queue[i + 1];
			i++;
		}
		data->queue.queue[i] = NULL;
	}
}