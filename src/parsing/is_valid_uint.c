/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 00:05:34 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/23 10:31:05 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdbool.h>

static bool	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v');
}

static bool	in_uint_range(char **str)
{
	uint64_t	result;
	uint8_t		current;

	result = 0;
	if (!ft_isdigit(**str))
		return (false);
	while (**str && ft_isdigit(**str))
	{
		current = **str - '0';
		result = (result * 10) + current;
		if (result > UINT32_MAX)
			return (false);
		(*str)++;
	}
	return (true);
}

bool	is_valid_uint(char *str)
{
	if (!*str)
		return (false);
	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	if (!in_uint_range(&str))
		return (false);
	while (ft_isspace(*str))
		str++;
	if (*str != 0)
		return (false);
	return (true);
}
