/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:43:39 by kecheong          #+#    #+#             */
/*   Updated: 2024/12/05 00:03:43 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "Minimap.h"
#include "Game.h"
#include "Map.h"
#include "Image.h"
#include "Vector.h"

// FIX: refactor this garbage

void	init_minimap(t_game *game, t_map *map, t_minimap *minimap)
{ (void)map;

	minimap->display = true;
	minimap->width = game->screen.width * MINIMAP_SCALE;
	minimap->height = game->screen.height * MINIMAP_SCALE;
	create_image(game->mlx, &minimap->img, minimap->width, minimap->height);
	minimap->img.pos.x = 10;
	minimap->img.pos.y = 10;
	update_minimap(minimap, game);
}

void	update_minimap(t_minimap *minimap, t_game *game)
{
	update_camera(&minimap->camera, minimap, &game->player);
	fill_minimap(&minimap->img, minimap->camera, &game->map, game, &game->player);
}

void	update_camera(t_camera *camera, t_minimap *minimap, t_player *player)
{
	const t_vec2d	p = player->world_pos;

	camera->centred_at = p;
	camera->half_dimension = (double)minimap->width / 2;
	camera->centre = (t_vec2d){camera->half_dimension, camera->half_dimension};
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
	t_vec2d	pos;
	t_vec2i	cam;

	pos.x = camera.top_left.x;
	pos.y = camera.top_left.y;
	cam.x = 0;
	cam.y = 0;
	fill_image(img, game->colours.cyan);
	draw_fov(img, &game->minimap, player, game); // HACK: we draw FOV first before layering the walls on top of it so the rays don't look like they're going through the walls
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
}

/* TODO: fix drawing rays to stop upon hitting a wall */
void	draw_fov(t_image *img, t_minimap *minimap, t_player *player, t_game *game)
{
	t_vec2i	start;
	t_vec2i	end;
	const double	angle_increment 
		= player->field_of_view / game->raycaster.number_of_rays;
	const double	leftmost_ray_angle
		= player->angle_in_radians + (player->field_of_view / 2);

	start.x = minimap->camera.centre.x;
	start.y = minimap->camera.centre.y;
	for (int i = 0; i < game->raycaster.number_of_rays; i++)
	{
		double	angle = leftmost_ray_angle - (i * angle_increment);
		double	dirX = cos(angle);
		double	dirY = -sin(angle);
		end.x = start.x + (dirX * 100); // FIX: hardcoded magnitude lol
		end.y = start.y + (dirY * 100);
		draw_line_in_image(img, start, end, game->colours.purple);
	}
}

