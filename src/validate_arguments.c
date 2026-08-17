/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_arguments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 00:02:51 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/18 00:32:00 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
