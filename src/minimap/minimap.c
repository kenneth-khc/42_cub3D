/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:43:39 by kecheong          #+#    #+#             */
/*   Updated: 2024/11/15 23:24:52 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minimap.h"
#include "Game.h"
#include "Map.h"
#include "Image.h"
#include "Vector.h"

// FIX: refactor this garbage

void	init_minimap(t_game *game, t_map *map, t_minimap *minimap)
{ (void)map;

	minimap->display = true;
	minimap->width = game->screen_width * MINIMAP_SCALE;
	minimap->height = game->screen_height * MINIMAP_SCALE;
	create_image(game->mlx, &minimap->img, minimap->width, minimap->height);
	update_minimap(minimap, game);
}

void	update_minimap(t_minimap *minimap, t_game *game)
{
	update_camera(&minimap->camera, minimap, &game->player);
	fill_minimap(&minimap->img, minimap->camera, &game->map, game, &game->player);
}

void	update_camera(t_camera *camera, t_minimap *minimap, t_player *player)
{
	const t_vector_double	p = player->world_pos;

	camera->centred_at = p;
	camera->half_dimension = (double)minimap->width / 2;
	camera->centre = (t_vector_double){camera->half_dimension, camera->half_dimension};
	camera->top_left.x = p.x - camera->half_dimension;
	camera->top_left.y = p.y - camera->half_dimension;
	camera->bot_right.x = p.x + camera->half_dimension;
	camera->bot_right.y = p.y + camera->half_dimension;
}

void	fill_minimap(t_image *img, t_camera camera, t_map *map, t_game *game, t_player *player)
{
	int				x = camera.top_left.x;
	int				map_x;
	int				map_y;
	t_vector_double	pos;
	t_vector_int	cam;

	pos.x = camera.top_left.x;
	pos.y = camera.top_left.y;
	cam.x = 0;
	cam.y = 0;
	fill_image(img, game->colours.cyan);
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
					draw_pixel(img, cam.x, cam.y, game->colours.grey);
				}
			}
			pos.x++;
			cam.x++;
		}
		pos.y++;
		cam.y++;
	}
	draw_border(img, 5, game->colours.black);
	draw_box(img, v2d_to_v2i(camera.centre), 5, game->colours.green);
	draw_fov(img, &game->minimap, player, game);
}

/* TODO: draw rays showing the fov instead of just one single line */
void	draw_fov(t_image *img, t_minimap *minimap, t_player *player, t_game *game)
{
	t_vector_int	start;
	t_vector_int	end;

	start.x = minimap->camera.centre.x;
	start.y = minimap->camera.centre.y;
	end.x = start.x + (player->direction.x * 20); // FIX: hardcoded magnitude lol
	end.y = start.y + (player->direction.y * 20);
	draw_line_in_image(img, start, end, game->colours.red);
}

