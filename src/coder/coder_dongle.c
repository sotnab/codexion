/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_dongle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 14:13:03 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/23 18:40:29 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <pthread.h>
#include "codexion.h"

bool	get_dongle(t_codexion *data, t_coder *coder, uint32_t index)
{
	uint32_t	time;
	t_dongle	*dongle;

	dongle = data->dongles + index;
	if (!dongle_request(data, coder, index))
		return (false);
	pthread_mutex_lock(&data->dongles[index].mutex);
	time = get_cpu_ms();
	// TODO sleeping while holding dongle makes no sense
	if (time < dongle->available_at)
		sleep_ms(data, dongle->available_at - time);
	print_coder_message(data, coder->number, DONGLE);
	return (true);
}

void	put_down_dongle(t_codexion *data, uint32_t index)
{
	t_dongle	*dongle;

	dongle = data->dongles + index;
	dongle->available_at = get_cpu_ms() + data->args->dongle_cooldown;
	pthread_mutex_unlock(&dongle->mutex);
}
