/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:11:39 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/15 20:33:22 by kecheong         ###   ########.fr       */
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
void	move_forward(void *ptr)
{
	t_game *const	game = (t_game *)ptr;
	t_player *const	player = &game->player;
	const double	dx = player->direction.x * player->speed;
	const double	dy = player->direction.y * player->speed;
	t_vec2d			test;

	test.x = player->world_pos.x + dx;
	test.y = player->world_pos.y;
	if (!collide(&game->map, &test, &game->tile))
	{
		player->delta.x += dx;
		player->is_moving = true;
	}
	test.x = player->world_pos.x;
	test.y = player->world_pos.y + dy;
	if (!collide(&game->map, &test, &game->tile))
	{
		player->delta.y += dy;
		player->is_moving = true;
	}
}

void	move_backward(void *ptr)
{
	t_game *const	game = (t_game *)ptr;
	t_player *const	player = &game->player;
	const double	dx = -player->direction.x * player->speed;
	const double	dy = -player->direction.y * player->speed;
	t_vec2d			test;

	test.x = player->world_pos.x + dx;
	test.y = player->world_pos.y;
	if (!collide(&game->map, &test, &game->tile))
	{
		player->delta.x += dx;
		player->is_moving = true;
	}
	test.x = player->world_pos.x;
	test.y = player->world_pos.y + dy;
	if (!collide(&game->map, &test, &game->tile))
	{
		player->delta.y += dy;
		player->is_moving = true;
	}
}

void	strafe_left(void *ptr)
{
	t_game *const	game = (t_game *)ptr;
	t_player *const	player = &game->player;
	const double	dx = cos(player->angle + M_PI_2) * player->speed;
	const double	dy = -sin(player->angle + M_PI_2) * player->speed;
	t_vec2d			test;

	test.x = player->world_pos.x + dx;
	test.y = player->world_pos.y;
	if (!collide(&game->map, &test, &game->tile))
	{
		player->delta.x += dx;
		player->is_moving = true;
	}
	test.x = player->world_pos.x;
	test.y = player->world_pos.y + dy;
	if (!collide(&game->map, &test, &game->tile))
	{
		player->delta.y += dy;
		player->is_moving = true;
	}
}

void	strafe_right(void *ptr)
{
	t_game *const	game = (t_game *)ptr;
	t_player *const	player = &game->player;
	const double	dx = cos(player->angle - M_PI_2) * player->speed;
	const double	dy = -sin(player->angle - M_PI_2) * player->speed;
	t_vec2d			test;

	test.x = player->world_pos.x + dx;
	test.y = player->world_pos.y;
	if (!collide(&game->map, &test, &game->tile))
	{
		player->delta.x += dx;
		player->is_moving = true;
	}
	test.x = player->world_pos.x;
	test.y = player->world_pos.y + dy;
	if (!collide(&game->map, &test, &game->tile))
	{
		player->delta.y += dy;
		player->is_moving = true;
	}
}
