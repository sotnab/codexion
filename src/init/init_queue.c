/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_queue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 12:51:02 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/23 13:41:43 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include "codexion.h"

bool	init_queue(t_codexion *data)
{
	t_queue		*queue;
	uint32_t	size;

	queue = &data->queue;
	size = sizeof(t_request *) * data->args->coders_number;
	queue->queue = malloc(size);
	if (!queue->queue)
		return (false);
	memset(queue->queue, 0, size);
	queue->scheduler = data->args->scheduler;
	if (pthread_cond_init(&queue->cond, NULL) != 0)
		return (free(queue->queue), false);
	return (true);
}
