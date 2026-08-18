/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_arguments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 00:02:51 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/18 21:21:35 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "codexion.h"

int	validate_arguments(char **argv)
{
	int	i;

	i = 1;
	while (i < 8)
		if (!is_valid_uint(argv[i++]))
			return (0);
	if (strcmp(argv[8], "fifo") != 0 && strcmp(argv[8], "edf") != 0)
		return (0);
	return (1);
}

int	parse_arguments(t_codexion *data, char **argv)
{
	if (!validate_arguments(argv))
		return (0);
	data->coders_number = atoi(argv[1]);
	data->burnout_time = atoi(argv[2]);
	data->compile_time = atoi(argv[3]);
	data->debug_time = atoi(argv[4]);
	data->refactor_time = atoi(argv[5]);
	data->compiles_required = atoi(argv[6]);
	data->dongle_cooldown = atoi(argv[7]);
	if (strcmp(argv[8], "fifo") == 0)
		data->scheduler = FIFO;
	else
		data->scheduler = EDF;
	return (1);
}
