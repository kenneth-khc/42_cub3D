/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 01:00:16 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/24 18:39:51 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Minimap.h"

t_minimap	init_minimap(t_game *game)
{
	t_minimap	minimap;
	const int	width = game->screen.width * MINIMAP_SCALE;
	const int	height = game->screen.height * MINIMAP_SCALE;

	minimap.img = create_image(game->mlx, width, height);
	minimap.img.pos.x = MINIMAP_X_OFFSET;
	minimap.img.pos.y = MINIMAP_Y_OFFSET;
	minimap.display = true;
	minimap.camera.half_dimension = (double)minimap.img.width / 2;
	minimap.camera.centre = (t_vec2d){minimap.camera.half_dimension,
		minimap.camera.half_dimension};
	minimap.background_colour = create_colour(0x00, 0x54, 0x88, 0xF7);
	minimap.wall_colour = create_colour(0x00, 0xAC, 0xA6, 0xB3);
	minimap.open_door_colour = create_colour(0x0, 0x0, 0x30, 0x30);
	minimap.closed_door_colour = create_colour(0x0, 0x0, 0xFF, 0x30);
	minimap.border_colour = create_colour(0x00, 0x00, 0x00, 0x00);
	minimap.border_thickness = 10;
	minimap.player_indicator_colour = create_colour(0x00, 0x00, 0xFF, 0x00);
	minimap.player_box_half_dimension = 30;
	minimap.direction_indicator_colour = create_colour(0x00, 0x00, 0x00, 0x00);
	return (minimap);
}
