/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 14:16:07 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/19 14:59:25 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "codexion.h"

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	while (1)
	{
		pthread_mutex_lock(coder->first_dongle);
		printf("%d has taken a dongle\n", coder->number);
		pthread_mutex_lock(coder->second_dongle);
		printf("%d has taken a dongle\n", coder->number);
		printf("%d is compiling\n", coder->number);
		usleep(coder->args->compile_time * 1000);
		pthread_mutex_unlock(coder->second_dongle);
		pthread_mutex_unlock(coder->first_dongle);
		printf("%d is debugging\n", coder->number);
		usleep(coder->args->debug_time * 1000);
		printf("%d is refactoring\n", coder->number);
		usleep(coder->args->refactor_time * 1000);
	}
	return (NULL);
}
