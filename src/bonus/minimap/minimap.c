/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:43:39 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/19 02:27:27 by kecheong         ###   ########.fr       */
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
	camera->half_dimension = (double)minimap->img.width / 2;
	camera->centre = (t_vec2d){camera->half_dimension, camera->half_dimension};
	camera->top_left.x = player.x - camera->half_dimension;
	camera->top_left.y = player.y - camera->half_dimension;
	camera->bot_right.x = player.x + camera->half_dimension;
	camera->bot_right.y = player.y + camera->half_dimension;
	fill_minimap(minimap, camera, &game->map, game);
}

void	draw_triangle(t_image *img, t_vec2d centre, t_game *game)
{
	draw_pixel(img, centre.x, centre.y, game->colours.black);

	double	dirX = game->player.direction.x * 20;
	double	dirY = game->player.direction.y * 20;
	/*printf("%f %f\n", dirX, dirY);*/
	draw_pixel(img, centre.x + dirX, centre.y + dirY, game->colours.black);

	t_vec2i	end = {.x = centre.x + dirX, .y = centre.y + dirY};
	draw_line_in_image(img, v2d_to_v2i(centre), end, game->colours.black);

	double	right_end = game->player.angle - degrees_to_radians(90);
	double	right_x = cos(right_end);
	double	right_y = -sin(right_end);

	t_vec2i	end2 = {.x = centre.x + right_x * 10, .y = centre.y + right_y * 10};
	draw_line_in_image(img, v2d_to_v2i(centre), end2, game->colours.black);

	double	left_end = game->player.angle + degrees_to_radians(90);
	double	left_x = cos(left_end);
	double	left_y = -sin(left_end);
	t_vec2i	end3 = {.x = centre.x + left_x * 10, .y = centre.y + left_y * 10};
	draw_line_in_image(img, v2d_to_v2i(centre), end3, game->colours.black);
}

void	fill_minimap(t_minimap *minimap, t_camera *camera, t_map *map, t_game *game)
{
	const int		x = camera->top_left.x;
	int				map_x;
	int				map_y;
	t_vec2d			pos;
	t_vec2i			cam;

	pos.x = camera->top_left.x;
	pos.y = camera->top_left.y;
	cam.x = 0;
	cam.y = 0;
	fill_image(&minimap->img, game->colours.cyan);
	while (pos.y < camera->bot_right.y)
	{
		pos.x = x;
		cam.x = 0;
		while (pos.x < camera->bot_right.x)
		{
			if (within_world_bounds(&pos, map, &game->tile))
			{
				map_x = pos.x / game->tile.width;
				map_y = pos.y / game->tile.height;
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
	draw_box(&minimap->img, v2d_to_v2i(camera->centre), 5, game->colours.green);
	draw_triangle(&minimap->img, camera->centre, game);
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
		= player->angle + (player->field_of_view / 2);
	int				i;

	i = 0;
	while (i < game->raycaster.ray_count)
	{
		draw_minimap_ray(minimap, leftmost_ray_angle - (i * angle_increment),
			game);
		i++;
	}
}
