/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 18:04:34 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/18 23:50:17 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "codexion.h"

static void	*coder_routine(void *arg)
{
	t_coder	*data;

	data = (t_coder *)arg;
	while (1)
	{
		pthread_mutex_lock(data->first_dongle);
		printf("%d has taken a dongle\n", data->number);
		pthread_mutex_lock(data->second_dongle);
		printf("%d has taken a dongle\n", data->number);
		printf("%d is compiling\n", data->number);
		usleep(data->codexion->compile_time * 1000);
		pthread_mutex_unlock(data->second_dongle);
		pthread_mutex_unlock(data->first_dongle);
		printf("%d is debugging\n", data->number);
		usleep(data->codexion->debug_time * 1000);
		printf("%d is refactoring\n", data->number);
		usleep(data->codexion->refactor_time * 1000);
	}
	return (NULL);
}

static int	init_dongles(pthread_mutex_t **dongles, unsigned int number)
{
	unsigned int	i;

	*dongles = malloc(sizeof(pthread_mutex_t) * number);
	if (!*dongles)
		return (0);
	i = 0;
	while (i < number)
		pthread_mutex_init(*dongles + (i++), NULL);
	return (1);
}

static int	init_coders(t_coder **coders,
	pthread_mutex_t *dongles, t_codexion *data)
{
	unsigned int	i;

	*coders = malloc(sizeof(t_coder) * data->coders_number);
	if (!*coders)
		return (0);
	i = 0;
	while (i < data->coders_number)
	{
		(*coders + i)->codexion = data;
		(*coders + i)->number = i + 1;
		if (i + 1 < data->coders_number)
		{
			(*coders + i)->first_dongle = dongles + i;
			(*coders + i)->second_dongle = dongles + i + 1;
		}
		else
		{
			(*coders + i)->first_dongle = dongles;
			(*coders + i)->second_dongle = dongles + i;
		}
		i++;
	}
	return (1);
}

void	codexion(t_codexion *data)
{
	pthread_mutex_t	*dongles;
	t_coder			*coders;
	unsigned int	i;

	if (!init_dongles(&dongles, data->coders_number))
		return ((void)fprintf(stderr, "Malloc failed.\n"));
	if (!init_coders(&coders, dongles, data))
		return (free(dongles), (void)fprintf(stderr, "Malloc failed.\n"));
	i = 0;
	while (i < data->coders_number)
	{
		pthread_create(&coders[i].thread, NULL, coder_routine, coders + i);
		i++;
	}
	i = 0;
	while (i < data->coders_number)
		pthread_join(coders[i++].thread, NULL);
}
