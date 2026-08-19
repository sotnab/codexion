/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_codexion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 14:17:53 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/19 15:31:36 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#include "codexion.h"

static bool	init_dongles(t_codexion *data)
{
	uint32_t	i;

	i = 0;
	while (i < data->args->coders_number)
		pthread_mutex_init(data->dongles + (i++), NULL);
	return (true);
}

static bool	init_coders(t_codexion *data)
{
	uint32_t	i;

	i = 0;
	while (i < data->args->coders_number)
	{
		data->coders[i].args = data->args;
		data->coders[i].number = i + 1;
		if (i + 1 < data->args->coders_number)
		{
			data->coders[i].first_dongle = data->dongles + i;
			data->coders[i].second_dongle = data->dongles + i + 1;
		}
		else
		{
			data->coders[i].first_dongle = data->dongles;
			data->coders[i].second_dongle = data->dongles + i;
		}
		i++;
	}
	return (true);
}

bool	init_codexion(t_codexion *data)
{
	data->dongles = malloc(sizeof(pthread_mutex_t) * data->args->coders_number);
	if (!data->dongles)
		return (false);
	init_dongles(data);
	data->coders = malloc(sizeof(t_coder) * data->args->coders_number);
	if (!data->coders)
		return (free(data->dongles), false);
	init_coders(data);
	return (true);
}
