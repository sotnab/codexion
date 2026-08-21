/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_codexion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 11:54:08 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/21 15:02:25 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include "codexion.h"

void	cleanup_codexion(t_codexion *data)
{
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->finish_lock);
	pthread_mutex_destroy(&data->queue_lock);
	pthread_cond_destroy(&data->queue.cond);
	free(data->coders);
	free(data->dongles);
	free(data->queue.queue);
}
