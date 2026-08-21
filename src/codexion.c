/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 18:04:34 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/21 17:58:42 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include "codexion.h"

static void	run_threads(t_codexion *data)
{
	uint32_t	i;
	void		**args;

	pthread_create(&data->monitor, NULL, monitor_routine, data);
	i = 0;
	while (i < data->args->coders_number)
	{
		args = malloc(sizeof(void *) * 2);
		if (!args)
			break ;
		args[0] = data;
		args[1] = data->coders + i;
		pthread_create(&data->coders[i].thread, NULL, coder_routine, args);
		i++;
	}
}

static void	join_threads(t_codexion *data)
{
	uint32_t	i;

	pthread_join(data->monitor, NULL);
	i = 0;
	while (i < data->args->coders_number)
		pthread_join(data->coders[i++].thread, NULL);
}

// get_cpu_ms() initializes static start time
void	codexion(t_args *args)
{
	t_codexion		data;

	data.args = args;
	data.finish = 0;
	if (!init_codexion(&data))
		return ((void)fprintf(stderr, "Malloc failed.\n"));
	get_cpu_ms();
	run_threads(&data);
	join_threads(&data);
	cleanup_codexion(&data);
}
