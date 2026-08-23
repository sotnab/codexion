/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_coders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 12:26:56 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/23 12:34:48 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "codexion.h"

static void	init_coder_data(t_coder *coder, uint32_t index, uint32_t length)
{
	memset(coder, 0, sizeof(t_coder));
	coder->number = index + 1;
	if (index % 2 == 0)
	{
		coder->first_dongle = index;
		coder->second_dongle = (index + 1) % length;
	}
	else
	{
		coder->first_dongle = (index + 1) % length;
		coder->second_dongle = index;
	}
}

bool	init_coders(t_codexion *data)
{
	uint32_t	i;
	uint32_t	length;

	length = data->args->coders_number;
	data->coders = malloc(sizeof(t_coder) * length);
	if (!data->coders)
		return (false);
	i = 0;
	while (i < length)
	{
		init_coder_data(data->coders + i, i, length);
		i++;
	}
	return (true);
}
