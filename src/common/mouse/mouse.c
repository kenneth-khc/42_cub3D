/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:39:37 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/22 05:43:30 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Player.h"
#include "Settings.h"
#include "Utils.h"
#include "Vector.h"
#include <mlx.h>
#include <math.h>

/* Process mouse movement to rotate the camera as appropriately */
int	process_mouse(int x, int y, void *param)
{
	t_game *const	game = (t_game*)param;
	t_player *const	player = &game->player;
	const t_vec2i	delta = {
		.x = SCREEN_WIDTH / 2 - x,
		.y = SCREEN_HEIGHT / 2 - y};

	if (x == SCREEN_WIDTH / 2 && y == SCREEN_HEIGHT / 2)
	{
		return (1);
	}
	player->angle += MOUSE_TURN_SPEED_RADS * delta.x;
	if (player->angle > radians(360))
	{
		player->angle -= radians(360);
	}
	else if (player->angle < radians(0))
	{
		player->angle += radians(360);
	}
	player->direction.x = cos(player->angle);
	player->direction.y = -sin(player->angle);
	mlx_mouse_move(game->mlx, game->window,
		SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	return (1);
}
