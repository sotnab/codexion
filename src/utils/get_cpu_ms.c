/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cpu_ms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 16:04:56 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/23 19:48:55 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "codexion.h"

void	sleep_ms(t_codexion *data, uint32_t duration)
{
	uint32_t	finish;

	finish = get_cpu_ms() + duration;
	while (!get_finish(data) && get_cpu_ms() < finish)
		usleep(1000);
}

static t_timespec	get_cpu_time(void)
{
	t_timespec	time;

	clock_gettime(CLOCK_REALTIME, &time);
	return (time);
}

t_timespec	get_timespec_from_ms(uint32_t ms)
{
	t_timespec	time;

	time.tv_sec = ms / 1000;
	time.tv_nsec = ms * 1000;
	return (time);
}

uint32_t	get_cpu_ms(void)
{
	static t_timespec	start = {-1, -1};
	t_timespec			time;
	uint32_t			time_delta;

	if (start.tv_sec == -1)
	{
		start = get_cpu_time();
		return (0);
	}
	time = get_cpu_time();
	time_delta = (time.tv_sec - start.tv_sec) * 1000;
	time_delta += (time.tv_nsec - start.tv_nsec) / 1000000;
	return (time_delta);
}
