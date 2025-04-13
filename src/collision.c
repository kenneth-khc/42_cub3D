/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 01:53:56 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/14 03:05:20 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Map.h"
#include "Vector.h"

bool	collide(t_map *map, t_vec2d *world_pos, t_game *game)
{
	t_vec2i	pos;

	pos.x = world_pos->x / game->tile_width;
	pos.y = world_pos->y / game->tile_height;
	if (map->layout[pos.y][pos.x] == '1')
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

bool	within_world_bounds(t_vec2d *world_pos, t_map *map, t_game *game)
{
	t_vec2i	m;
	bool	within_x_axis;
	bool	within_y_axis;

	if (world_pos->x < 0 || world_pos->y < 0)
	{
		return (false);
	}
	m.x = world_pos->x / game->tile_width;
	m.y = world_pos->y / game->tile_height;
	within_x_axis = m.x >= 0 && m.x < map->width;
	within_y_axis = m.y >= 0 && m.y < map->height;
	return (within_x_axis && within_y_axis);
}
