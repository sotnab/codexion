/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_heapify.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 14:29:40 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/23 16:15:03 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "codexion.h"

static void	request_swap(t_request **a, t_request **b)
{
	void	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	queue_heapify_up(t_queue *queue)
{
	uint32_t	index;
	uint32_t	parent;

	if (queue->size < 2)
		return ;
	index = queue->size - 1;
	while (index != 0)
	{
		parent = (index - 1) / 2;
		if (queue->queue[index]->deadline >= queue->queue[parent]->deadline)
			break ;
		request_swap(queue->queue + index, queue->queue + parent);
		index = parent;
	}
}

void	queue_heapify_down(t_queue *queue)
{
	uint32_t	index;
	uint32_t	left;
	uint32_t	right;
	uint32_t	smallest;

	index = 0;
	while (1)
	{
		left = 2 * index + 1;
		right = 2 * index + 2;
		smallest = index;
		if (left < queue->size
			&& queue->queue[left]->deadline < queue->queue[smallest]->deadline)
			smallest = left;
		if (right < queue->size
			&& queue->queue[right]->deadline < queue->queue[smallest]->deadline)
			smallest = right;
		if (smallest == index)
			break ;
		request_swap(queue->queue + index, queue->queue + smallest);
		index = smallest;
	}
}
