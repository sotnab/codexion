/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 15:53:23 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/19 16:30:26 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "codexion.h"

void	*monitor_routine(void *arg)
{
	t_codexion	*data;

	data = (t_codexion *)arg;
	(void)data;
	return (NULL);
}
