/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 18:04:34 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/19 15:14:18 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include "codexion.h"

static void	run_coders(t_codexion *data)
{
	uint32_t	i;

	i = 0;
	while (i < data->args->coders_number)
	{
		pthread_create(&data->coders[i].thread, NULL,
			coder_routine, data->coders + i);
		i++;
	}
}

static void	join_coders(t_codexion *data)
{
	uint32_t	i;

	i = 0;
	while (i < data->args->coders_number)
		pthread_join(data->coders[i++].thread, NULL);
}

void	codexion(t_args *args)
{
	t_codexion		data;

	data.args = args;
	if (!init_codexion(&data))
		return ((void)fprintf(stderr, "Malloc failed.\n"));
	run_coders(&data);
	join_coders(&data);
}
