/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:39:37 by kecheong          #+#    #+#             */
/*   Updated: 2024/11/15 16:40:54 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "Game.h"

/* Process mouse movement to rotate the camera as appropriately */
int	process_mouse(int x, int y, void *param)
{
	t_game *const	game = (t_game*)param;
	t_player *const	player = &game->player; (void)player;
	static int		previous_x = -1;
	int				dx;

	(void)y;
	if (previous_x == -1)
		previous_x = x;
	else
	{
		dx = x - previous_x;
		if (dx < 0) // rotate right
		{
			player->angle_in_radians += (0.01 * abs(dx));
			if (radians_to_degrees(player->angle_in_radians) > 360)
			{
				player->angle_in_radians -= degrees_to_radians(360);
			}
		}
		else
		{
			player->angle_in_radians -= (0.01 * abs(dx));
			if (radians_to_degrees(player->angle_in_radians < 0))
			{
				player->angle_in_radians += degrees_to_radians(360);
			}
		}
		player->direction.x = cos(player->angle_in_radians);
		player->direction.y = -sin(player->angle_in_radians);
		previous_x = x;
		update_minimap(&game->minimap, game);
	}
	return (0);
}
