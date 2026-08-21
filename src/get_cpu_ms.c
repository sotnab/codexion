/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cpu_ms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 16:04:56 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/20 21:23:24 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include "codexion.h"

uint32_t	get_cpu_ms(void)
{
	static t_timespec	start = {-1, -1};
	t_timespec			time;
	uint32_t			time_delta;

	if (start.tv_sec == -1)
	{
		clock_gettime(CLOCK_REALTIME, &start);
		return (0);
	}
	clock_gettime(CLOCK_REALTIME, &time);
	time_delta = (time.tv_sec - start.tv_sec) * 1000;
	time_delta += (time.tv_nsec - start.tv_nsec) / 1e6;
	return (time_delta);
}
