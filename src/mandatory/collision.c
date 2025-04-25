/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 01:53:56 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/25 22:14:56 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Map.h"
#include "Vector.h"

bool	movable(t_vec2d pos, t_map *map, t_dimensions tile)
{
	t_vec2i	tile_index;

	tile_index.x = pos.x / tile.width;
	tile_index.y = pos.y / tile.height;
	if (map->layout[tile_index.y][tile_index.x] == '1')
	{
		return (false);
	}
	else
	{
		return (true);
	}
}
