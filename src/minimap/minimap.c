/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:43:39 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/14 01:18:47 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minimap.h"
#include "Game.h"
#include "Map.h"
#include "Image.h"
#include "Vector.h"
#include <math.h>

void	update_minimap(t_minimap *minimap, t_game *game)
{
	const t_vec2d	player = game->player.world_pos;
	t_camera *const	camera = &minimap->camera;

	camera->centred_at = player;
	camera->half_dimension = (double)minimap->width / 2;
	camera->centre = (t_vec2d){camera->half_dimension, camera->half_dimension};
	camera->top_left.x = player.x - camera->half_dimension;
	camera->top_left.y = player.y - camera->half_dimension;
	camera->bot_right.x = player.x + camera->half_dimension;
	camera->bot_right.y = player.y + camera->half_dimension;
	fill_minimap(minimap, &game->map, game);
}

void	fill_minimap(t_minimap *minimap, t_map *map, t_game *game)
{
	const t_camera	camera = minimap->camera;
	const int		x = camera.top_left.x;
	int				map_x;
	int				map_y;
	t_vec2d			pos;
	t_vec2i			cam;

	pos.x = camera.top_left.x;
	pos.y = camera.top_left.y;
	cam.x = 0;
	cam.y = 0;
	fill_image(&minimap->img, game->colours.cyan);
	while (pos.y < camera.bot_right.y)
	{
		pos.x = x;
		cam.x = 0;
		while (pos.x < camera.bot_right.x)
		{
			if (within_world_bounds(&pos, map, game))
			{
				map_x = pos.x / game->tile_width;
				map_y = pos.y / game->tile_height;
				if (map->layout[map_y][map_x] == '1')
				{
					draw_pixel(&minimap->img, cam.x, cam.y, game->colours.grey);
				}
			}
			pos.x++;
			cam.x++;
		}
		pos.y++;
		cam.y++;
	}
	draw_border(&minimap->img, 5, game->colours.black);
	draw_box(&minimap->img, v2d_to_v2i(camera.centre), 5, game->colours.green);
}

static void	draw_minimap_ray(t_minimap *minimap, double angle, t_game *game)
{
	const t_vec2i	start = {
		.x = minimap->camera.centre.x,
		.y = minimap->camera.centre.y
	};
	const double	dir_x = cos(angle);
	const double	dir_y = -sin(angle);
	const t_vec2i	end = {
		.x = start.x + (dir_x * 100),
		.y = start.x + (dir_y * 100)
	};

	draw_line_in_image(&minimap->img, start, end, game->colours.purple);
}

/* TODO: fix drawing rays to stop upon hitting a wall
 * or discard this idea entirely */
void	draw_fov(t_minimap *minimap, t_player *player,
	t_game *game)
{
	const double	angle_increment
		= player->field_of_view / game->raycaster.ray_count;
	const double	leftmost_ray_angle
		= player->angle_in_radians + (player->field_of_view / 2);
	int				i;

	i = 0;
	while (i < game->raycaster.ray_count)
	{
		draw_minimap_ray(minimap, leftmost_ray_angle - (i * angle_increment),
			game);
		i++;
	}
}
