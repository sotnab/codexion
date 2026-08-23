/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_finish.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 18:11:41 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/23 18:19:48 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <pthread.h>
#include "codexion.h"

bool	get_finish(t_codexion *data)
{
	bool	finish;

	pthread_mutex_lock(&data->finish_lock);
	finish = data->finish;
	pthread_mutex_unlock(&data->finish_lock);
	return (finish);
}
