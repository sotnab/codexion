/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 15:53:23 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/23 15:41:53 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include "codexion.h"

static bool	is_burnout(t_codexion *data)
{
	uint32_t	i;
	uint32_t	time;

	i = 0;
	time = get_cpu_ms();
	while (i < data->args->coders_number)
	{
		if (data->coders[i].last_compile + data->args->burnout_time < time)
			return (burnout(data, i + 1), true);
		i++;
	}
	return (false);
}

static bool	is_finished(t_codexion *data)
{
	uint32_t	i;

	i = 0;
	while (i < data->args->coders_number)
	{
		if (data->coders[i].compiles < data->args->compiles_required)
			return (false);
		i++;
	}
	return (finish(data), true);
}

void	*monitor_routine(void *arg)
{
	t_codexion	*data;

	data = (t_codexion *)arg;
	while (!is_burnout(data) && !is_finished(data))
		usleep(5000);
	return (NULL);
}
