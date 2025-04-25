/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:43:39 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/26 05:02:09 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minimap.h"
#include "Doors.h"
#include "Game.h"
#include "Map.h"
#include "Image.h"
#include "Vector.h"
#include "Doors.h"

static void
draw_walls(t_minimap *minimap, t_camera *camera, t_map *map);

static void
draw_doors(t_minimap *minimap, t_camera *camera, t_map *map, t_doors *doors);

static bool
is_a_wall(t_vec2d *pos, t_map *map);

static bool
out_of_bounds(t_vec2d *pos, t_map *map);

void	update_minimap(t_minimap *minimap, t_vec2d *player_pos, t_game *game)
{
	t_camera *const	camera = &minimap->camera;

	camera->top_left.x = player_pos->x - camera->half_dimension;
	camera->top_left.y = player_pos->y - camera->half_dimension;
	camera->bot_right.x = player_pos->x + camera->half_dimension;
	camera->bot_right.y = player_pos->y + camera->half_dimension;
	fill_image(&minimap->img, minimap->background_colour);
	draw_walls(minimap, camera, &game->map);
	draw_doors(minimap, camera, &game->map, &game->doors);
	draw_border(&minimap->img, minimap->border_thickness,
		minimap->border_colour);
	draw_player_indicator(minimap, camera, &game->player);
}

static
void	draw_doors(t_minimap *minimap, t_camera *camera, t_map *map,
				t_doors *doors)
{
	t_vec2d		world_pos;
	t_vec2i		draw_pos;

	world_pos = camera->top_left;
	draw_pos = (t_vec2i){.x = 0, .y = 0};
	while (world_pos.y++ < camera->bot_right.y)
	{
		draw_pos.x = 0;
		world_pos.x = camera->top_left.x;
		while (world_pos.x++ < camera->bot_right.x)
		{
			if (!out_of_bounds(&world_pos, map))
			{
				if (is_closed_door(&world_pos, doors))
					draw_pixel(&minimap->img, draw_pos.x, draw_pos.y,
						minimap->closed_door_colour);
				else if (is_open_door(&world_pos, doors))
					draw_pixel(&minimap->img, draw_pos.x, draw_pos.y,
						minimap->open_door_colour);
			}
			draw_pos.x++;
		}
		draw_pos.y++;
	}
}

static
void	draw_walls(t_minimap *minimap, t_camera *camera, t_map *map)
{
	t_vec2d		world_pos;
	t_vec2i		draw_pos;

	world_pos = camera->top_left;
	draw_pos = (t_vec2i){.x = 0, .y = 0};
	while (world_pos.y < camera->bot_right.y)
	{
		draw_pos.x = 0;
		world_pos.x = camera->top_left.x;
		while (world_pos.x < camera->bot_right.x)
		{
			if (!out_of_bounds(&world_pos, map))
			{
				if (is_a_wall(&world_pos, map))
				{
					draw_pixel(&minimap->img, draw_pos.x, draw_pos.y,
						minimap->wall_colour);
				}
			}
			world_pos.x++;
			draw_pos.x++;
		}
		world_pos.y++;
		draw_pos.y++;
	}
}

static bool	is_a_wall(t_vec2d *pos, t_map *map)
{
	bool	within_x_axis;
	bool	within_y_axis;
	t_vec2i	tile_index;

	tile_index.x = pos->x / TILE_WIDTH;
	tile_index.y = pos->y / TILE_HEIGHT;
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

static bool	out_of_bounds(t_vec2d *pos, t_map *map)
{
	t_vec2i	tile;

	tile.x = pos->x / TILE_WIDTH;
	tile.y = pos->y / TILE_HEIGHT;
	if (tile.x < 1 || tile.y < 1
		|| tile.x >= map->width - 1 || tile.y >= map->height - 1)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}
