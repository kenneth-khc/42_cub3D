/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 01:53:56 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/15 20:33:02 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Map.h"
#include "Vector.h"
#include <math.h>

bool	collide(t_map *map, t_vec2d *world_pos, t_dimensions *tile)
{
	t_vec2d	pos;

	pos.x = floor(world_pos->x / tile->width);
	pos.y = floor(world_pos->y / tile->height);
	if (map->layout[(int)pos.y][(int)pos.x] == '1')
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

bool	within_world_bounds(t_vec2d *world_pos, t_map *map, t_dimensions *tile)
{
	t_vec2i	m;
	bool	within_x_axis;
	bool	within_y_axis;

	if (world_pos->x < 0 || world_pos->y < 0)
	{
		return (false);
	}
	m.x = world_pos->x / tile->width;
	m.y = world_pos->y / tile->height;
	within_x_axis = m.x >= 0 && m.x < map->width;
	within_y_axis = m.y >= 0 && m.y < map->height;
	return (within_x_axis && within_y_axis);
}
