/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:43:39 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/24 19:14:35 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minimap.h"
#include "Doors.h"
#include "Game.h"
#include "Map.h"
#include "Image.h"
#include "Vector.h"

static void
draw_walls(t_minimap *minimap, t_camera *camera, t_map *map, t_door_states *doors);
static bool
in_game_and_is_wall(t_vec2d *pos, t_map *map);

void	update_minimap(t_minimap *minimap, t_vec2d *player_pos, t_game *game)
{
	t_camera *const	camera = &minimap->camera;

	camera->top_left.x = player_pos->x - camera->half_dimension;
	camera->top_left.y = player_pos->y - camera->half_dimension;
	camera->bot_right.x = player_pos->x + camera->half_dimension;
	camera->bot_right.y = player_pos->y + camera->half_dimension;
	fill_image(&minimap->img, minimap->background_colour);
	draw_walls(minimap, camera, &game->map, &game->door_states);
	draw_border(&minimap->img, minimap->border_thickness,
		minimap->border_colour);
	draw_player_indicator(minimap, camera, &game->player);
}

#include "Doors.h"

bool	is_open_door(t_vec2d *world_pos, t_door_states *doors)
{
	t_vec2i	tile;
	t_door	*door;

	tile.x = world_pos->x / 50;
	tile.y = world_pos->y / 50;
	door = get_door(doors, tile.x, tile.y);
	if (door->is_door && !door->is_closed)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

bool	is_closed_door(t_vec2d *world_pos, t_door_states *doors)
{
	t_vec2i	tile;
	t_door	*door;

	tile.x = world_pos->x / 50;
	tile.y = world_pos->y / 50;
	door = get_door(doors, tile.x, tile.y);
	if (door->is_door && door->is_closed)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

bool	out_of_bounds(t_vec2d *pos, t_map *map)
{
	t_vec2i	tile;

	tile.x = pos->x / 50;
	tile.y = pos->y / 50;
	if (tile.x < 1 || tile.y < 1 || tile.x >= map->width - 1 || tile.y >= map->height - 1)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

static void	draw_walls(t_minimap *minimap, t_camera *camera, t_map *map, t_door_states *doors)
{
	t_vec2d	world_pos;
	t_vec2i	draw_pos;

	world_pos = camera->top_left;
	draw_pos = (t_vec2i){.x = 0, .y = 0};
	while (world_pos.y < camera->bot_right.y)
	{
		draw_pos.x = 0;
		world_pos.x = camera->top_left.x;
		while (world_pos.x < camera->bot_right.x)
		{
			if (out_of_bounds(&world_pos, map))
			{
				world_pos.x++;
				draw_pos.x++;
				continue ;
			}
			if (in_game_and_is_wall(&world_pos, map))
			{
				draw_pixel(&minimap->img, draw_pos.x, draw_pos.y,
					minimap->wall_colour);
			}
			else if (is_open_door(&world_pos, doors))
			{
				draw_pixel(&minimap->img, draw_pos.x, draw_pos.y, minimap->open_door_colour);
			}
			else if (is_closed_door(&world_pos, doors))
			{
				draw_pixel(&minimap->img, draw_pos.x, draw_pos.y, minimap->closed_door_colour);

			}
			world_pos.x++;
			draw_pos.x++;
		}
		world_pos.y++;
		draw_pos.y++;
	}
}

static bool	in_game_and_is_wall(t_vec2d *pos, t_map *map)
{
	bool	within_x_axis;
	bool	within_y_axis;
	t_vec2i	tile_index;

	if (pos->x < 0 || pos->y < 0)
	{
		return (false);
	}
	tile_index.x = pos->x / 50;
	tile_index.y = pos->y / 50;
\
	within_x_axis = tile_index.x > 0 && tile_index.x < map->width;
	within_y_axis = tile_index.y > 0 && tile_index.y < map->height;
	if (within_x_axis && within_y_axis)
	{
		return (map->layout[tile_index.y][tile_index.x] == '1');
	}
	else
	{
		return (false);
	}
}
