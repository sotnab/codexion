/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 20:31:48 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/19 14:30:10 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "codexion.h"

int	main(int argc, char **argv)
{
	t_args	data;

	if (argc != 9)
		return (fprintf(stderr, "Invalid number of arguments.\n"), 1);
	if (parse_arguments(&data, argv))
		codexion(&data);
	else
		return (printf("Invalid arguments.\n"), 1);
	return (0);
}
