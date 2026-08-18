/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaran <wbaran@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 00:05:34 by wbaran            #+#    #+#             */
/*   Updated: 2026/08/18 10:35:46 by wbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v');
}

static int	in_uint_range(char **str)
{
	long	result;
	int		current;

	result = 0;
	if (!ft_isdigit(**str))
		return (0);
	while (**str && ft_isdigit(**str))
	{
		current = **str - '0';
		if (result != 0 && ((UINT_MAX - current) / result) < 10)
			return (0);
		result = (result * 10) + current;
		(*str)++;
	}
	return (1);
}

int	is_valid_uint(char *str)
{
	if (!*str)
		return (0);
	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	if (!in_uint_range(&str))
		return (0);
	while (ft_isspace(*str))
		str++;
	if (*str != 0)
		return (0);
	return (1);
}
