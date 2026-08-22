/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_heapify.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 14:29:40 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/22 14:31:41 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	request_swap(t_request **a, t_request **b)
{
	void	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	queue_heapify_up(t_codexion *data)
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

void	queue_heapify_down(t_codexion *data)
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
