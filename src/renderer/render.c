/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 22:31:10 by kecheong          #+#    #+#             */
/*   Updated: 2024/10/30 22:32:44 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <mlx.h>
#include "Game.h"
#include "Image.h"

void	draw_wall(t_image *world, int screen_x, double wall_height, t_game *game)
{
	int				y;
	const int		half_screen_y = game->screen_height / 2;
	const double	half_wall_height = wall_height / 2;
	t_colour	red = {.s_component = {.alpha = 0x00, .red = 0x55, .green = 0x55, .blue = 0x55}};

	y = half_screen_y;
	t_vector_int	center_point = {.x = screen_x, .y = half_screen_y};
	t_vector_int	upper_end = {.x = screen_x, .y = y - half_wall_height};
	t_vector_int	lower_end = {.x = screen_x, .y = y + half_wall_height};
	draw_line_in_image(world, center_point, upper_end, red);
	draw_line_in_image(world, center_point, lower_end, red);
}

void	render(t_game *game, t_raycaster *raycaster)
{
	int		i;
	t_ray	*ray;
	double	distance_to_hwall;
	double	distance_to_vwall;
	const t_player	*player = &game->player;

	i = 0;
	while (i < raycaster->number_of_rays)
	{
		ray = &raycaster->rays[i];
		distance_to_hwall = fabs(player->world_pos.x - ray->horizontal_wall_pos.x) / cos(ray->angle_in_radians);
		distance_to_vwall = fabs(player->world_pos.x - ray->vertical_wall_pos.x) / cos(ray->angle_in_radians);
		if (distance_to_vwall < distance_to_hwall)
		{
			draw_wall(&game->world, i, distance_to_vwall, game);
		}
		else
		{
			draw_wall(&game->world, i, distance_to_hwall, game);
		}
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->window, game->world.instance, 0, 0);
	mlx_put_image_to_window(game->mlx, game->window, game->map.img.instance, 0, 0);
}

void	init_background(t_game *game)
{
	int			y;
	int			x;
	t_colour	purple;
	t_colour	grey;

	y = 0;
	// TODO: fix image initializations
	create_image(game->mlx, &game->world, game->screen_width, game->screen_height);
	purple = (t_colour){.s_component = {.alpha = 0x00, .red = 0xAE, .green = 0x71, .blue = 0xF5}};
	grey = (t_colour){.s_component = {.alpha = 0x00, .red = 0xAC, .green = 0xA6, .blue = 0xb3}};
	y = 0;
	while (y < game->screen_height / 2)
	{
		x = 0;
		while (x < game->screen_width)
		{
			*get_pixel_addr(&game->world, x, y) = purple.value;
			x++;
		}
		y++;
	}
	while (y < game->screen_height)
	{
		x = 0;
		while (x < game->screen_width)
		{
			*get_pixel_addr(&game->world, x, y) = grey.value;
			x++;
		}
		y++;
	}
}

