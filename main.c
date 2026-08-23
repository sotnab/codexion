/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 20:31:48 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/23 10:25:23 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "codexion.h"

int	main(int argc, char **argv)
{
	t_args	args;

	if (argc != 9)
		return (fprintf(stderr, "Invalid number of arguments.\n"), 1);
	if (!parse_arguments(&args, argv))
		return (fprintf(stderr, "Invalid arguments.\n"), 1);
	codexion(&args);
	return (0);
}
