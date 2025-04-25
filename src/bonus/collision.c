/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 01:53:56 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/26 04:28:33 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Map.h"
#include "Doors.h"
#include "Vector.h"
#include "Settings.h"

bool	movable(t_vec2d pos, t_map *map, t_doors *doors)
{
	t_vec2i	tile_index;
	t_door	*door;

	tile_index.x = pos.x / TILE_WIDTH;
	tile_index.y = pos.y / TILE_HEIGHT;
	door = get_door(doors, tile_index.x, tile_index.y);
	if (map->layout[tile_index.y][tile_index.x] == '1'
		|| (door && door->is_closed))
	{
		return (false);
	}
	else
	{
		return (true);
	}
}
