/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 22:31:10 by kecheong          #+#    #+#             */
/*   Updated: 2024/11/14 18:11:57 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include "Game.h"
#include "Image.h"
#include "Renderer.h"
#include "Vector.h"
#include "Map.h"
#include <assert.h>

void	render(t_game *game, t_raycaster *raycaster)
{
	t_ray	*ray;
	double	line_height;

	// TODO: debugging, if world3d doesn't exist we don't render it
	if (game->world_3d.instance)
	{
		clear_walls(game);
		for (int x = 0; x < game->screen_width; x++)
		{
			ray = &raycaster->rays[x];
			line_height = game->screen_height / ray->distance_travelled;
			draw_wall(&game->world_3d, x, line_height, game);
		}
		put_image(game, &game->world_3d, &(t_vector_int){0, 0});
	}
	if (game->minimap.img.instance && game->minimap.display)
	{
		put_image(game, &game->minimap.img, &(t_vector_int){10, 10});
	}
}

/* Clear away walls on the screen by redrawing the ceiling and floor */
void	clear_walls(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->screen_height / 2)
	{
		x = 0;
		while (x < game->screen_width)
		{
			draw_pixel(&game->world_3d, x, y, game->colours.purple);
			x++;
		}
		y++;
	}
	while (y < game->screen_height)
	{
		x = 0;
		while (x < game->screen_width)
		{
			draw_pixel(&game->world_3d, x, y, game->colours.grey);
			x++;
		}
		y++;
	}
}

void	draw_wall(t_image *world, int screen_x, double wall_height, t_game *game)
{
	/*int				y;*/
	/*const int		half_screen_y = game->screen_height / 2;*/
	/*const double	half_wall_height = wall_height / 2;*/
	/**/
	/*y = half_screen_y;*/
	/*t_vector_int	center_point = {.x = screen_x, .y = half_screen_y};*/
	/*t_vector_int	upper_end = {.x = screen_x, .y = y - half_wall_height};*/
	/*t_vector_int	lower_end = {.x = screen_x, .y = y + half_wall_height};*/
	/*draw_vertical(world, center_point, upper_end, game->colours.white);*/
	/*draw_vertical(world, center_point, lower_end, game->colours.white);*/

	t_vector_int	draw_start;
	draw_start.y = (int)-wall_height / 2 + game->screen_height / 2;
	draw_start.x = screen_x;
	if (draw_start.y < 0)
	{
		draw_start.y = 0;
	}
	t_vector_int	draw_end;
	draw_end.y = (int)wall_height / 2 + game->screen_height / 2;
	draw_end.x = screen_x;
	if (draw_end.y > 0)
	{
		draw_end.y = game->screen_height - 1;
	}
	draw_vertical(world, draw_start, draw_end, game->colours.white);
}

void	init_world_3d(t_game *game)
{
	int			y;
	int			x;

	// TODO: fix image initializations
	create_image(game->mlx, &game->world_3d, game->screen_width, game->screen_height);
	y = 0;
	while (y < game->screen_height / 2)
	{
		x = 0;
		while (x < game->screen_width)
		{
			draw_pixel(&game->world_3d, x, y, game->colours.purple);
			x++;
		}
		y++;
	}
	while (y < game->screen_height)
	{
		x = 0;
		while (x < game->screen_width)
		{
			draw_pixel(&game->world_3d, x, y, game->colours.grey);
			x++;
		}
		y++;
	}
}

