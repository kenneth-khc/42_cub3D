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

#include <mlx.h>
#include "Game.h"

void	render(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->window, game->ceiling.instance, 0, 0);
	mlx_put_image_to_window(game->mlx, game->window, game->floor.instance, 0, game->screen_height / 2);
	mlx_put_image_to_window(game->mlx, game->window, game->map.img.instance, 0, 0);
}

void	init_background(t_image *floor, t_image *ceiling, t_game *game)
{
	int			y;
	int			x;
	t_colour	purple;
	t_colour	grey;

	y = 0;
	create_image(game->mlx, floor, game->screen_width, game->screen_height / 2);
	create_image(game->mlx, ceiling, game->screen_width, game->screen_height / 2);
	purple = (t_colour){.s_component = {.alpha = 0x00, .red = 0xAE, .green = 0x71, .blue = 0xF5}};
	grey = (t_colour){.s_component = {.alpha = 0x00, .red = 0xAC, .green = 0xA6, .blue = 0xb3}};
	while (y < ceiling->height)
	{
		x = 0;
		while (x < ceiling->width)
		{
			*get_pixel_addr(ceiling, x, y) = purple.value;
			x++;
		}
		y++;
	}
	y = 0;
	while (y < floor->height)
	{
		x = 0;
		while (x < floor->width)
		{
			*get_pixel_addr(floor, x, y) = grey.value;
			x++;
		}
		y++;
	}
}

