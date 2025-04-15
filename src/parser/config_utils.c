/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 05:35:32 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/17 05:45:31 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	identified(const char *line, const char *identifier)
{
	const size_t	identifier_len = ft_strlen(identifier);
	size_t			i;

	i = 0;
	while (i < identifier_len)
	{
		if (line[i] != identifier[i])
		{
			return (false);
		}
		else
		{
			i++;
		}
	}
	return (true);
}

bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v');
}
