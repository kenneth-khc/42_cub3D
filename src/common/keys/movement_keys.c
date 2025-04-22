/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:11:39 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/23 01:31:43 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Vector.h"
#include "Player.h"
#include "Map.h"
#include <math.h>

// TODO: fix diagonal movement into walls

/* For player movement, WASD is used
 * W - move player forward
 * S - move player backward
 * A - strafe player to the left (move in +90 degrees)
 * D - strafe player to the right (move in -90 degrees)
 */
int	move_forward(void *ptr)
{
	t_game *const	game = (t_game *)ptr;
	t_player *const	player = &game->player;
	const double	dx = player->direction.x * player->speed;
	const double	dy = player->direction.y * player->speed;
	const t_vec2d	ori = player->world_pos;

	if (movable((t_vec2d){ori.x + dx, ori.y}, &game->map, game->tile))
	{
		player->world_pos.x += dx;
	}
	if (movable((t_vec2d){ori.x, ori.y + dy}, &game->map, game->tile))
	{
		player->world_pos.y += dy;
	}
	return (1);
}

int	move_backward(void *ptr)
{
	t_game *const	game = (t_game *)ptr;
	t_player *const	player = &game->player;
	const double	dx = -player->direction.x * player->speed;
	const double	dy = -player->direction.y * player->speed;
	const t_vec2d	ori = player->world_pos;

	if (movable((t_vec2d){ori.x + dx, ori.y}, &game->map, game->tile))
	{
		player->world_pos.x += dx;
	}
	if (movable((t_vec2d){ori.x, ori.y + dy}, &game->map, game->tile))
	{
		player->world_pos.y += dy;
	}
	return (1);
}

int	strafe_left(void *ptr)
{
	t_game *const	game = (t_game *)ptr;
	t_player *const	player = &game->player;
	const double	dx = cos(player->angle + M_PI_2) * player->speed;
	const double	dy = -sin(player->angle + M_PI_2) * player->speed;
	const t_vec2d	ori = player->world_pos;

	if (movable((t_vec2d){ori.x + dx, ori.y}, &game->map, game->tile))
	{
		player->world_pos.x += dx;
	}
	if (movable((t_vec2d){ori.x, ori.y + dy}, &game->map, game->tile))
	{
		player->world_pos.y += dy;
	}
	return (1);
}

int	strafe_right(void *ptr)
{
	t_game *const	game = (t_game *)ptr;
	t_player *const	player = &game->player;
	const double	dx = cos(player->angle - M_PI_2) * player->speed;
	const double	dy = -sin(player->angle - M_PI_2) * player->speed;
	const t_vec2d	ori = player->world_pos;

	if (movable((t_vec2d){ori.x + dx, ori.y}, &game->map, game->tile))
	{
		player->world_pos.x += dx;
	}
	if (movable((t_vec2d){ori.x, ori.y + dy}, &game->map, game->tile))
	{
		player->world_pos.y += dy;
	}
	return (1);
}
