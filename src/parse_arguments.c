/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 00:02:51 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/19 15:32:11 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "codexion.h"

bool	validate_arguments(char **argv)
{
	uint32_t	i;

	i = 1;
	while (i < 8)
		if (!is_valid_uint(argv[i++]))
			return (false);
	if (strcmp(argv[8], "fifo") != 0 && strcmp(argv[8], "edf") != 0)
		return (false);
	return (true);
}

bool	parse_arguments(t_args *args, char **argv)
{
	if (!validate_arguments(argv))
		return (false);
	args->coders_number = atoi(argv[1]);
	args->burnout_time = atoi(argv[2]);
	args->compile_time = atoi(argv[3]);
	args->debug_time = atoi(argv[4]);
	args->refactor_time = atoi(argv[5]);
	args->compiles_required = atoi(argv[6]);
	args->dongle_cooldown = atoi(argv[7]);
	if (strcmp(argv[8], "fifo") == 0)
		args->scheduler = FIFO;
	else
		args->scheduler = EDF;
	return (true);
}
