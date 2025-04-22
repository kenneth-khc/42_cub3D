/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 07:08:15 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/23 00:47:52 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "Map.h"

bool	is_wall(t_map *map, int x, int y)
{
	return (map->layout[y][x] == '1' || map->layout[y][x] == ' ');
}

bool	is_wall_or_padding(char c)
{
	return (c == '1' || c == ' ');
}

bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v');
}

bool	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

bool	is_floor(char c)
{
	return (c == '0' || is_player(c));
}

bool	is_valid_map_character(char c)
{
	return (c == ' ' || c == '0' || c == '1'
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
