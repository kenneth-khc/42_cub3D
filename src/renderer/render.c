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

void	clear_walls(t_game *game)
{
	int				y;
	int				x;
	const t_colour	purple = create_colour(0x00, 0xAE, 0x71, 0xF5);
	const t_colour	grey = create_colour(0x00, 0xAC, 0xA6, 0xB3);

	y = 0;
	while (y < game->screen_height / 2)
	{
		x = 0;
		while (x < game->screen_width)
		{
			draw_pixel(&game->world_3d, x, y, purple);
			x++;
		}
		y++;
	}
	while (y < game->screen_height)
	{
		x = 0;
		while (x < game->screen_width)
		{
			draw_pixel(&game->world_3d, x, y, grey);
			x++;
		}
		y++;
	}
}

void	draw_wall(t_image *world, int screen_x, double wall_height, t_game *game)
{
	int				y;
	const int		half_screen_y = game->screen_height / 2;
	const double	half_wall_height = wall_height / 2;
	const t_colour	red = create_colour(0x00, 0x55, 0x55, 0x55);

	y = half_screen_y;
	t_vector_int	center_point = {.x = screen_x, .y = half_screen_y};
	t_vector_int	upper_end = {.x = screen_x, .y = y - half_wall_height};
	t_vector_int	lower_end = {.x = screen_x, .y = y + half_wall_height};
	draw_vertical(world, center_point, upper_end, red);
	draw_vertical(world, center_point, lower_end, red);
}

void	init_world_3d(t_game *game)
{
	int			y;
	int			x;
	t_colour	purple;
	t_colour	grey;

	// TODO: fix image initializations
	create_image(game->mlx, &game->world_3d, game->screen_width, game->screen_height);
	purple = create_colour(0x00, 0xAE, 0x71, 0xF5);
	grey = create_colour(0x00, 0xAC, 0xA6, 0xB3);
	y = 0;
	while (y < game->screen_height / 2)
	{
		x = 0;
		while (x < game->screen_width)
		{
			draw_pixel(&game->world_3d, x, y, purple);
			x++;
		}
		y++;
	}
	while (y < game->screen_height)
	{
		x = 0;
		while (x < game->screen_width)
		{
			draw_pixel(&game->world_3d, x, y, grey);
			x++;
		}
		y++;
	}
}

