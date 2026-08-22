/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_request.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 14:40:22 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/22 14:44:39 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "codexion.h"

static bool	is_my_turn(t_codexion *data, t_coder *coder, uint32_t index)
{
	t_request	*first_request;
	bool		my_turn;

	if (data->queue.size == 0)
		return (false);
	first_request = data->queue.queue[0];
	my_turn = first_request->number == coder->number
		&& first_request->dongle_index == index;
	if (my_turn)
	{
		queue_pop_request(data);
		pthread_cond_broadcast(&data->queue.cond);
	}
	return (my_turn);
}

static t_request	*create_request(
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

void	dongle_request(t_codexion *data, t_coder *coder, uint32_t index)
{
	t_request	*request;

	request = create_request(data, coder, index);
	if (!request)
		return ;
	pthread_mutex_lock(&data->queue_lock);
	queue_add_request(data, request);
	pthread_cond_broadcast(&data->queue.cond);
	while (!is_my_turn(data, coder, index) && !data->finish)
		pthread_cond_wait(&data->queue.cond, &data->queue_lock);
	pthread_mutex_unlock(&data->queue_lock);
	if (data->finish)
		return ;
	pthread_mutex_lock(&data->dongles[index]);
}
