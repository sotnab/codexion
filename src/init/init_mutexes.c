/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 13:34:24 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/23 22:10:03 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <pthread.h>
#include "codexion.h"

bool	init_mutexes(t_codexion *data)
{
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&data->finish_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_lock);
		return (false);
	}
	if (pthread_mutex_init(&data->queue_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_lock);
		pthread_mutex_destroy(&data->finish_lock);
		return (false);
	}
	if (pthread_mutex_init(&data->data_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_lock);
		pthread_mutex_destroy(&data->finish_lock);
		pthread_mutex_destroy(&data->queue_lock);
		return (false);
	}
	return (true);
}
