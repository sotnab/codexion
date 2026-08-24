/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_request.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 14:40:22 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/24 19:35:22 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include "codexion.h"

// TODO shitty code
static bool	is_my_turn(t_codexion *data, t_coder *coder, uint32_t index)
{
	t_request	*first;
	bool		my_turn;

	if (data->queue.size == 0)
		return (false);
	first = data->queue.queue[0];
	my_turn = first->number == coder->number
		&& first->dongle_index == index
		&& get_available_at(data, index) < get_cpu_ms();
	if (my_turn)
	{
		queue_pop_request(data);
		pthread_cond_broadcast(&data->queue.cond);
	}
	return (my_turn);
}

// TODO shitty code
bool	dongle_request(t_codexion *data, t_coder *coder, uint32_t index)
{
	t_request	*request;
	t_timespec	available_at;

	available_at = get_timespec_from_ms(get_available_at(data, index));
	request = create_request(data, coder, index);
	if (!request)
		return (false);
	pthread_mutex_lock(&data->queue_lock);
	queue_add_request(data, request);
	while (!is_my_turn(data, coder, index) && !data->finish)
		pthread_cond_timedwait(&data->queue.cond,
			&data->queue_lock, &available_at);
	pthread_mutex_unlock(&data->queue_lock);
	return (true);
}
