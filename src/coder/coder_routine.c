/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 14:16:07 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/23 14:56:20 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include "codexion.h"

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
	while (!data->finish)
	{
		get_dongle(data, coder, coder->first_dongle);
		get_dongle(data, coder, coder->second_dongle);
		coder_compile(data, coder);
		put_down_dongle(data, coder->second_dongle);
		put_down_dongle(data, coder->first_dongle);
		coder->compiles++;
		coder_debug_refactor(data, coder);
	}
	return (free(arg), NULL);
}
