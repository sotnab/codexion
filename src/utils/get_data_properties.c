/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_properties.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 18:11:41 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/24 15:41:57 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <pthread.h>
#include "codexion.h"

bool	get_finish(t_codexion *data)
{
	bool	finish;

	pthread_mutex_lock(&data->data_lock);
	finish = data->finish;
	pthread_mutex_unlock(&data->data_lock);
	return (finish);
}

bool	get_compiles_finished(t_codexion *data, t_coder *coder)
{
	bool	result;

	pthread_mutex_lock(&data->data_lock);
	if (coder->compiles >= data->args->compiles_required)
		result = true;
	else
		result = false;
	pthread_mutex_unlock(&data->data_lock);
	return (result);
}

uint32_t	get_available_at(t_codexion *data, uint32_t index)
{
	uint32_t	result;

	pthread_mutex_lock(&data->data_lock);
	result = data->dongles[index].available_at;
	pthread_mutex_unlock(&data->data_lock);
	return (result);
}
