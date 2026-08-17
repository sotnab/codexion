/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 18:04:34 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/18 00:32:26 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "codexion.h"

// number_of_coders time_to_burnout time_to_compile time_to_debug
// time_to_refactor number_of_compiles_required dongle_cooldown scheduler

int	main(int argc, char **argv)
{
	if (argc != 9)
		return (fprintf(stderr, "Invalid number of arguments.\n"), 1);
	if (validate_arguments(argv))
		printf("Valid arguments.\n");
	else
		printf("Invalid arguments.\n");
	return (0);
}
