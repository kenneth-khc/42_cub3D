/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 08:53:03 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/26 09:10:50 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.h"
#include "Utils.h"
#include "libft.h"
#include <stdbool.h>

static bool	is_valid_map_character(char c);

void	parse_map_content(t_config *config, char *line)
{
	size_t			i;
	const size_t	line_len = ft_strlen(line);

	i = 0;
	while (i < line_len)
	{
		if (!is_valid_map_character(line[i]))
		{
			error("Invalid map character\n");
		}
		i++;
	}
	add_row(&config->map, line);
}

static bool	is_valid_map_character(char c)
{
	return (c == ' ' || c == '0' || c == '1'
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
