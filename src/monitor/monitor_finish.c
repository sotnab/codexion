/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 15:40:03 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/23 15:40:55 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include "codexion.h"

static void	set_finish(t_codexion *data)
{
	pthread_mutex_lock(&data->finish_lock);
	data->finish = true;
	pthread_mutex_unlock(&data->finish_lock);
	pthread_cond_broadcast(&data->queue.cond);
}

void	burnout(t_codexion *data, int number)
{
	pthread_mutex_lock(&data->print_lock);
	set_finish(data);
	printf("%d burned out\n", number);
	pthread_mutex_unlock(&data->print_lock);
}

void	finish(t_codexion *data)
{
	pthread_mutex_lock(&data->print_lock);
	set_finish(data);
	printf("Every coder compiled: %d times\n", data->args->compiles_required);
	pthread_mutex_unlock(&data->print_lock);
}
