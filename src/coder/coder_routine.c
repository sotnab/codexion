/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 14:16:07 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/23 21:30:42 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include "codexion.h"

static bool	get_dongle(t_codexion *data, t_coder *coder, uint32_t index)
{
	if (!dongle_request(data, coder, index))
		return (false);
	pthread_mutex_lock(&data->dongles[index].lock);
	print_coder_message(data, coder->number, DONGLE);
	return (true);
}

static void	put_down_dongle(t_codexion *data, uint32_t index)
{
	t_dongle	*dongle;

	dongle = data->dongles + index;
	dongle->available_at = get_cpu_ms() + data->args->dongle_cooldown;
	pthread_mutex_unlock(&dongle->lock);
}

static void	coder_compile(t_codexion *data, t_coder *coder)
{
	print_coder_message(data, coder->number, COMPILING);
	coder->last_compile = get_cpu_ms();
	sleep_ms(data, data->args->compile_time);
}

static void	coder_debug_refactor(t_codexion *data, t_coder *coder)
{
	print_coder_message(data, coder->number, DEBUGGING);
	sleep_ms(data, data->args->debug_time);
	print_coder_message(data, coder->number, REFACTORING);
	sleep_ms(data, data->args->refactor_time);
}

void	*coder_routine(void *arg)
{
	t_codexion	*data;
	t_coder		*coder;

	if (!arg)
		return (NULL);
	data = (t_codexion *)((void **)arg)[0];
	coder = (t_coder *)((void **)arg)[1];
	while (!get_finish(data))
	{
		if (!get_dongle(data, coder, coder->first_dongle))
			break ;
		if (!get_dongle(data, coder, coder->second_dongle))
			break ;
		coder_compile(data, coder);
		put_down_dongle(data, coder->second_dongle);
		put_down_dongle(data, coder->first_dongle);
		coder->compiles++;
		coder_debug_refactor(data, coder);
	}
	return (free(arg), NULL);
}
