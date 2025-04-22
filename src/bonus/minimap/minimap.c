/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:43:39 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/23 22:57:58 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minimap.h"
#include "Game.h"
#include "Map.h"
#include "Image.h"
#include "Vector.h"
#include "Utils.h"
#include <math.h>

static void
draw_walls(t_minimap *minimap, t_camera *camera, t_map *map);
static bool
in_game_and_is_wall(t_vec2d *pos, t_map *map);
static void
draw_player_indicator(t_minimap *minimap, t_camera *camera);
static void
draw_direction_indicator(t_minimap *minimap, t_vec2d centre, t_player *player);

void	update_minimap(t_minimap *minimap, t_vec2d *player_pos, t_game *game)
{
	t_camera *const	camera = &minimap->camera;

	camera->top_left.x = player_pos->x - camera->half_dimension;
	camera->top_left.y = player_pos->y - camera->half_dimension;
	camera->bot_right.x = player_pos->x + camera->half_dimension;
	camera->bot_right.y = player_pos->y + camera->half_dimension;
	fill_image(&minimap->img, minimap->background_colour);
	draw_walls(minimap, camera, &game->map);
	draw_border(&minimap->img, minimap->border_thickness,
		minimap->border_colour);
	draw_player_indicator(minimap, camera);
	draw_direction_indicator(minimap, camera->centre, &game->player);
}

static void	draw_walls(t_minimap *minimap, t_camera *camera, t_map *map)
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
			if (in_game_and_is_wall(&world_pos, map))
			{
				draw_pixel(&minimap->img, draw_pos.x, draw_pos.y,
					minimap->wall_colour);
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

static void	draw_player_indicator(t_minimap *minimap, t_camera *camera)
{
	t_vec2i	start;
	t_vec2i	end;
	int		x;

	start.x = camera->centre.x - minimap->player_box_half_dimension;
	start.y = camera->centre.y - minimap->player_box_half_dimension;
	end.x = camera->centre.x + minimap->player_box_half_dimension;
	end.y = camera->centre.y + minimap->player_box_half_dimension;
	x = start.x;
	while (start.y != end.y)
	{
		start.x = x;
		while (start.x != end.x)
		{
			draw_pixel(&minimap->img, start.x, start.y,
				minimap->player_indicator_colour);
			start.x++;
		}
		start.y++;
	}
}

static
void	draw_direction_indicator(t_minimap *minimap, t_vec2d centre,
	t_player *player)
{
	const double	left_dir = player->angle + radians(90);
	const double	right_dir = player->angle - radians(90);
	t_vec2i			front_end;
	t_vec2i			right_end;
	t_vec2i			left_end;

	front_end.x = centre.x + player->direction.x * 20;
	front_end.y = centre.y + player->direction.y * 20;
	draw_line_in_image(&minimap->img, vec2i(centre), front_end,
		minimap->direction_indicator_colour);
\
	right_end.x = centre.x + cos(right_dir) * 10;
	right_end.y = centre.y + -sin(right_dir) * 10;
	draw_line_in_image(&minimap->img, vec2i(centre), right_end,
		minimap->direction_indicator_colour);
\
	left_end.x = centre.x + cos(left_dir) * 10;
	left_end.y = centre.y + -sin(left_dir) * 10;
	draw_line_in_image(&minimap->img, vec2i(centre), left_end,
		minimap->direction_indicator_colour);
}
