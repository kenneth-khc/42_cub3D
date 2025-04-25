/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:11:39 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/26 04:35:10 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Keys.h"
#include "Vector.h"
#include "Player.h"
#include "Map.h"
#include <math.h>

bool	movable(t_vec2d pos, t_map *map, t_doors *doors);

/* Move the player by dy and dx and calculate its new tile index within
 * the map */
static void	move_player(t_player *player, double dx, double dy)
{
	player->world_pos.x += dx;
	player->world_pos.y += dy;
	player->tile_index.x = player->world_pos.x / TILE_WIDTH;
	player->tile_index.y = player->world_pos.y / TILE_HEIGHT;
	player->is_moving = true;
}

/* For player movement, WASD is used
 * W - move player forward
 * S - move player backward
 * A - strafe player to the left (move in +90 degrees)
 * D - strafe player to the right (move in -90 degrees)
 */
int	move_forward(t_game *game)
{
	t_player *const	player = &game->player;
	const double	dx = player->direction.x * player->speed;
	const double	dy = player->direction.y * player->speed;
	const t_vec2d	ori = player->world_pos;

	if (movable((t_vec2d){ori.x + dx, ori.y}, &game->map, &game->doors))
	{
		move_player(player, dx, 0);
	}
	if (movable((t_vec2d){ori.x, ori.y + dy}, &game->map, &game->doors))
	{
		move_player(player, 0, dy);
	}
	return (1);
}

int	move_backward(t_game *game)
{
	t_player *const	player = &game->player;
	const double	dx = -player->direction.x * player->speed;
	const double	dy = -player->direction.y * player->speed;
	const t_vec2d	ori = player->world_pos;

	if (movable((t_vec2d){ori.x + dx, ori.y}, &game->map, &game->doors))
	{
		move_player(player, dx, 0);
	}
	if (movable((t_vec2d){ori.x, ori.y + dy}, &game->map, &game->doors))
	{
		move_player(player, 0, dy);
	}
	return (1);
}

int	strafe_left(t_game *game)
{
	t_player *const	player = &game->player;
	const double	dx = cos(player->angle + M_PI_2) * player->speed;
	const double	dy = -sin(player->angle + M_PI_2) * player->speed;
	const t_vec2d	ori = player->world_pos;

	if (movable((t_vec2d){ori.x + dx, ori.y}, &game->map, &game->doors))
	{
		move_player(player, dx, 0);
	}
	if (movable((t_vec2d){ori.x, ori.y + dy}, &game->map, &game->doors))
	{
		move_player(player, 0, dy);
	}
	return (1);
}

int	strafe_right(t_game *game)
{
	t_player *const	player = &game->player;
	const double	dx = cos(player->angle - M_PI_2) * player->speed;
	const double	dy = -sin(player->angle - M_PI_2) * player->speed;
	const t_vec2d	ori = player->world_pos;

	if (movable((t_vec2d){ori.x + dx, ori.y}, &game->map, &game->doors))
	{
		move_player(player, dx, 0);
	}
	if (movable((t_vec2d){ori.x, ori.y + dy}, &game->map, &game->doors))
	{
		move_player(player, 0, dy);
	}
	return (1);
}
