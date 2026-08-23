/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 15:53:23 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/22 13:56:15 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include "codexion.h"

static void	set_finish(t_codexion *data)
{
	pthread_mutex_lock(&data->finish_lock);
	data->finish = true;
	pthread_mutex_unlock(&data->finish_lock);
	pthread_cond_broadcast(&data->queue.cond);
}

static void	burnout(t_codexion *data, int number)
{
	pthread_mutex_lock(&data->print_lock);
	set_finish(data);
	printf("%d burned out\n", number);
	pthread_mutex_unlock(&data->print_lock);
}

static void	finish(t_codexion *data)
{
	pthread_mutex_lock(&data->print_lock);
	set_finish(data);
	printf("Every coder compiled: %d times\n", data->args->compiles_required);
	pthread_mutex_unlock(&data->print_lock);
}

void	*monitor_routine(void *arg)
{
	t_codexion	*data;
	t_coder		*coder;
	bool		finished;
	uint32_t	time;
	uint32_t	i;

	data = (t_codexion *)arg;
	while (true)
	{
		i = 0;
		time = get_cpu_ms();
		finished = true;
		while (i < data->args->coders_number)
		{
			coder = data->coders + (i++);
			if (time - coder->last_compile > data->args->burnout_time)
				return (burnout(data, coder->number), NULL);
			if (coder->compiles < data->args->compiles_required)
				finished = false;
		}
		if (finished)
			return (finish(data), NULL);
		usleep(5000);
	}
	return (NULL);
}
