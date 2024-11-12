/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 22:31:10 by kecheong          #+#    #+#             */
/*   Updated: 2024/11/12 13:54:57 by kecheong         ###   ########.fr       */
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

void
draw_wall(t_image *world, int screen_x, double wall_height, t_game *game);

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
			draw_pixel(&game->world3D, x, y, purple);
			x++;
		}
		y++;
	}
	while (y < game->screen_height)
	{
		x = 0;
		while (x < game->screen_width)
		{
			draw_pixel(&game->world3D, x, y, grey);
			x++;
		}
		y++;
	}
}

void	render(t_game *game, t_raycaster *raycaster)
{ (void)game; (void)raycaster;

	t_ray	*ray;
	double	line_height;

	clear_walls(game);
	ray = &raycaster->rays[0];
	for (int x = 0; x < game->screen_width; x++)
	{
		ray = &raycaster->rays[x];
		if (ray->distance_to_h_wall < ray->distance_to_v_wall)
		{
			line_height = game->screen_height / ray->distance_to_h_wall;
			draw_wall(&game->world3D, x, line_height, game);
		}
		else
		{
			line_height = game->screen_height / ray->distance_to_v_wall;
			draw_wall(&game->world3D, x, line_height, game);
		}
		/*printf("Line to draw: %f\n", line_height);*/
	}
	put_image(game, &game->world3D, &(t_vector_int){0, 0});
}

void	draw_wall(t_image *world, int screen_x, double wall_height, t_game *game)
{ (void)world;
	if (wall_height == 0)
	{
		wall_height = game->screen_height;
	}
	/*else*/
	/*{*/
	/*	wall_height = game->screen_height / wall_height;*/
	/*}*/
	int				y;
	const int		half_screen_y = game->screen_height / 2;
	const double	half_wall_height = wall_height / 2;
	t_colour		red = {.s_component = {.alpha = 0x00, .red = 0x55, .green = 0x55, .blue = 0x55}};

	y = half_screen_y;
	t_vector_int	center_point = {.x = screen_x, .y = half_screen_y};
	t_vector_int	upper_end = {.x = screen_x, .y = y - half_wall_height};
	t_vector_int	lower_end = {.x = screen_x, .y = y + half_wall_height};
	draw_line_in_image(world, center_point, upper_end, red);
	draw_line_in_image(world, center_point, lower_end, red);
}

void	init_world3D(t_game *game)
{
	int			y;
	int			x;
	t_colour	purple;
	t_colour	grey;

	y = 0;
	// TODO: fix image initializations
	create_image(game->mlx, &game->world3D, game->screen_width, game->screen_height);
	purple = (t_colour){.s_component = {.alpha = 0x00, .red = 0xAE, .green = 0x71, .blue = 0xF5}};
	grey = (t_colour){.s_component = {.alpha = 0x00, .red = 0xAC, .green = 0xA6, .blue = 0xb3}};
	y = 0;
	while (y < game->screen_height / 2)
	{
		x = 0;
		while (x < game->screen_width)
		{
			draw_pixel(&game->world3D, x, y, purple);
			x++;
		}
		y++;
	}
	while (y < game->screen_height)
	{
		x = 0;
		while (x < game->screen_width)
		{
			/**get_pixel_addr(&game->world3D, x - game->world3D.width, y) = grey.value;*/
			draw_pixel(&game->world3D, x, y, grey);
			x++;
		}
		y++;
	}
}

