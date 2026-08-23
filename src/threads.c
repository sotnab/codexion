/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 10:25:46 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/23 13:50:10 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include "codexion.h"

static void	**create_thread_args(t_codexion *data, uint32_t index)
{
	void	**args;

	args = malloc(sizeof(void *) * 2);
	if (!args)
		return (NULL);
	args[0] = data;
	args[1] = data->coders + index;
	return (args);
}

void	run_threads(t_codexion *data)
{
	uint32_t	i;

	pthread_create(&data->monitor, NULL, monitor_routine, data);
	i = 0;
	while (i < data->args->coders_number)
	{
		pthread_create(&data->coders[i].thread, NULL,
			coder_routine, create_thread_args(data, i));
		i++;
	}
}

void	join_threads(t_codexion *data)
{
	uint32_t	i;

	i = 0;
	while (i < data->args->coders_number)
		pthread_join(data->coders[i++].thread, NULL);
	pthread_join(data->monitor, NULL);
}