/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_codexion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 14:17:53 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/23 21:21:16 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#include "codexion.h"

static void	first_cleanup(t_codexion *data)
{
	uint32_t	length;

	length = data->args->coders_number;
	destroy_dongle_mutexes(data, length, length);
	free(data->dongles);
}

static void	second_cleanup(t_codexion *data)
{
	first_cleanup(data);
	free(data->coders);
}

static void	third_cleanup(t_codexion *data)
{
	second_cleanup(data);
	pthread_cond_destroy(&data->queue.cond);
	free(data->queue.queue);
}

bool	init_codexion(t_codexion *data, t_args *args)
{
	memset(data, 0, sizeof(t_codexion));
	data->args = args;
	if (!init_dongles(data))
		return (false);
	if (!init_coders(data))
		return (first_cleanup(data), false);
	if (!init_queue(data))
		return (second_cleanup(data), false);
	if (!init_mutexes(data))
		return (third_cleanup(data), false);
	return (true);
}
