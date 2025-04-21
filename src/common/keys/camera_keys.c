/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:47:58 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/19 22:21:23 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Settings.h"
#include "Keys.h"
#include "Utils.h"
#include <math.h>

/* The player starts at a certain angle based on the input of the map.
 * (E)ast  - 0 degrees   | 0 or 2PI radians
 * (N)orth - 90 degrees  | PI/2 radians
 * (W)est  - 180 degrees | PI radians
 * (S)outh - 270 degrees | 3PI/2 radians
 *
 * By pressing the left arrow key, increment the angle (going counterclockwise)
 * and the player's field of view moves to the left accordingly
 * By pressing the right arrow key, decrement the angle (going clockwise)
 * and the field of view moves to the right accordingly */
int	rotate_left(void *ptr)
{
	t_game *const	game = (t_game *)ptr;
	t_player *const	player = &game->player;

	player->angle += TURN_SPEED_RADS;
	if (player->angle > radians(360))
	{
		player->angle -= radians(360);
	}
	player->direction.x = cos(player->angle);
	player->direction.y = -sin(player->angle);
	return (1);
}

int	rotate_right(void *ptr)
{
	t_game *const	game = (t_game *)ptr;
	t_player *const	player = &game->player;

	player->angle -= TURN_SPEED_RADS;
	if (player->angle < radians(0))
	{
		player->angle += radians(360);
	}
	player->direction.x = cos(player->angle);
	player->direction.y = -sin(player->angle);
	return (1);
}

int	look_up(void *ptr)
{
	t_game *const		game = (t_game *)ptr;
	static const int	upper_bound = SCREEN_HEIGHT - SCREEN_HEIGHT / 4;

	if (game->renderer.midpoint < upper_bound)
	{
		game->renderer.midpoint += VERTICAL_CAMERA_SPEED;
	}
	return (1);
}

int	look_down(void *ptr)
{
	t_game *const		game = (t_game *)ptr;
	static const int	lower_bound = SCREEN_HEIGHT / 4;

	if (game->renderer.midpoint > lower_bound)
	{
		game->renderer.midpoint -= VERTICAL_CAMERA_SPEED;
	}
	return (1);
}
