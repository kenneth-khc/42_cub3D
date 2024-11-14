/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:43:39 by kecheong          #+#    #+#             */
/*   Updated: 2024/11/14 18:36:06 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minimap.h"
#include <stdio.h>
#include "Game.h"
#include "Map.h"
#include "Image.h"
#include "Vector.h"

void	init_camera(t_camera *camera, t_game *game, t_player *player)
{ (void)game;
	const t_vector_double	p = player->world_pos;

	camera->centre = (t_vector_double){100, 100};
	camera->half_dimension = 100.0;
	camera->offset.x = camera->centre.x - player->world_pos.x;
	camera->offset.y = camera->centre.y - player->world_pos.y;
	camera->top_left.x = p.x - camera->half_dimension;
	camera->top_left.y = p.y - camera->half_dimension;
	camera->top_right.x = p.x + camera->half_dimension;
	camera->top_right.y = p.y - camera->half_dimension;
	camera->bot_left.x = p.x - camera->half_dimension;
	camera->bot_left.y = p.y + camera->half_dimension;
	camera->bot_right.x = p.x + camera->half_dimension;
	camera->bot_right.y = p.y + camera->half_dimension;
}

void	fill_minimap(t_image *img, t_camera camera, t_map *map, t_game *game)
{
	int	x = camera.top_left.x;
	int	map_x;
	int	map_y;
	t_vector_double	pos;
	t_vector_int	cam;

	pos.x = camera.top_left.x;
	pos.y = camera.top_left.y;
	cam.x = 0;
	cam.y = 0;
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
					draw_pixel(img, cam.x, cam.y, game->colours.purple);
				}
			}
			else
			{
				draw_pixel(img, cam.x, cam.y, game->colours.black);
			}
			pos.x++;
			cam.x++;
		}
		pos.y++;
		cam.y++;
	}
}

void	init_minimap(t_game *game, t_map *map, t_minimap *minimap)
{ (void)map;

	minimap->display = true;
	minimap->width = game->screen_width * MINIMAP_SCALE;
	minimap->height = game->screen_height * MINIMAP_SCALE;
	init_camera(&minimap->camera, game, &game->player);
	create_image(game->mlx, &minimap->img, minimap->width, minimap->height);
	fill_image(&minimap->img, game->colours.cyan);
	fill_minimap(&minimap->img, minimap->camera, map, game);
	draw_box(&minimap->img, v2d_to_v2i(minimap->camera.centre), 5, game->colours.green);
}
