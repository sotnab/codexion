/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dongles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 12:48:31 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/23 21:32:34 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#include <string.h>
#include "codexion.h"

void	destroy_dongle_mutexes(t_codexion *data, uint32_t n1, uint32_t n2)
{
	uint32_t	i;

	i = 0;
	while (i < n1)
		pthread_mutex_destroy(&data->dongles[i++].lock);
	i = 0;
	while (i < n2)
		pthread_mutex_destroy(&data->dongles[i++].data_lock);
}

static bool	init_dongle_mutexes(t_codexion *data)
{
	uint32_t	i;

	i = 0;
	while (i < data->args->coders_number)
	{
		if (pthread_mutex_init(&data->dongles[i].lock, NULL) != 0)
			return (destroy_dongle_mutexes(data, i, i), false);
		if (pthread_mutex_init(&data->dongles[i].data_lock, NULL) != 0)
			return (destroy_dongle_mutexes(data, i + 1, i), false);
		i++;
	}
	return (true);
}

bool	init_dongles(t_codexion *data)
{
	uint32_t	size;

	size = sizeof(t_dongle) * data->args->coders_number;
	data->dongles = malloc(size);
	if (!data->dongles)
		return (false);
	memset(data->dongles, 0, size);
	if (!init_dongle_mutexes(data))
		return (free(data->dongles), false);
	return (true);
}
