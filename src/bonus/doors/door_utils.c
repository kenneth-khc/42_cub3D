/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 04:56:18 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/26 05:12:14 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Doors.h"
#include "Settings.h"
#include <stddef.h>

t_door	*get_door(t_doors *doors, int x, int y)
{
	t_door	*door;

	door = doors->ptr;
	while (door->tile_pos.x != -1 && door->tile_pos.y != -1)
	{
		if (door->tile_pos.x == x && door->tile_pos.y == y)
		{
			return (door);
		}
		door++;
	}
	return (NULL);
}

bool	is_open_door(t_vec2d *world_pos, t_doors *doors)
{
	t_vec2i	tile;
	t_door	*door;

	tile.x = world_pos->x / TILE_WIDTH;
	tile.y = world_pos->y / TILE_HEIGHT;
	door = get_door(doors, tile.x, tile.y);
	if (door && !door->is_closed)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

bool	is_closed_door(t_vec2d *world_pos, t_doors *doors)
{
	t_vec2i	tile;
	t_door	*door;

	tile.x = world_pos->x / TILE_WIDTH;
	tile.y = world_pos->y / TILE_HEIGHT;
	door = get_door(doors, tile.x, tile.y);
	if (door && door->is_closed)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}
