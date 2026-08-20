/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 15:53:23 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/20 12:45:14 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include "codexion.h"

static void	print_burnout_message(t_codexion *data, int number)
{
	pthread_mutex_lock(&data->print_lock);
	printf("%d burned out\n", number);
	pthread_mutex_unlock(&data->print_lock);
}

static void	burnout(t_codexion *data, int number)
{
	pthread_mutex_lock(&data->burnout_lock);
	data->burned_out = true;
	pthread_mutex_unlock(&data->burnout_lock);
	print_burnout_message(data, number);
}

void	*monitor_routine(void *arg)
{
	t_codexion	*data;
	t_coder		*coder;
	uint32_t	time;
	uint32_t	i;

	data = (t_codexion *)arg;
	while (true)
	{
		i = 0;
		time = get_cpu_ms();
		while (i < data->args->coders_number)
		{
			coder = data->coders + i;
			if (time - coder->last_compile > data->args->burnout_time)
				return (burnout(data, coder->number), NULL);
			i++;
		}
		usleep(5000);
	}
	return (NULL);
}
