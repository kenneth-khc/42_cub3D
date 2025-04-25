/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:11:39 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/25 22:16:36 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Keys.h"
#include "Vector.h"
#include "Player.h"
#include "Map.h"
#include <math.h>
#include <stdio.h>

bool	movable(t_vec2d pos, t_map *map, t_dimensions tile, t_door_states *doors_state);

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

	if (movable((t_vec2d){ori.x + dx, ori.y}, &game->map, game->tile, &game->door_states))
	{
		player->world_pos.x += dx;
		player->tile_index.x = player->world_pos.x / game->tile.width;
		player->is_moving = true;
	}
	if (movable((t_vec2d){ori.x, ori.y + dy}, &game->map, game->tile, &game->door_states))
	{
		player->world_pos.y += dy;
		player->tile_index.y = player->world_pos.y / game->tile.height;
		player->is_moving = true;
	}
	return (1);
}

int	move_backward(t_game *game)
{
	t_player *const	player = &game->player;
	const double	dx = -player->direction.x * player->speed;
	const double	dy = -player->direction.y * player->speed;
	const t_vec2d	ori = player->world_pos;

	if (movable((t_vec2d){ori.x + dx, ori.y}, &game->map, game->tile, &game->door_states))
	{
		player->world_pos.x += dx;
		player->tile_index.x = player->world_pos.x / game->tile.width;
		player->is_moving = true;
	}
	if (movable((t_vec2d){ori.x, ori.y + dy}, &game->map, game->tile, &game->door_states))
	{
		player->world_pos.y += dy;
		player->tile_index.y = player->world_pos.y / game->tile.height;
		player->is_moving = true;
	}
	return (1);
}

int	strafe_left(t_game *game)
{
	t_player *const	player = &game->player;
	const double	dx = cos(player->angle + M_PI_2) * player->speed;
	const double	dy = -sin(player->angle + M_PI_2) * player->speed;
	const t_vec2d	ori = player->world_pos;

	if (movable((t_vec2d){ori.x + dx, ori.y}, &game->map, game->tile, &game->door_states))
	{
		player->world_pos.x += dx;
		player->tile_index.x = player->world_pos.x / game->tile.width;
		player->is_moving = true;
	}
	if (movable((t_vec2d){ori.x, ori.y + dy}, &game->map, game->tile, &game->door_states))
	{
		player->world_pos.y += dy;
		player->tile_index.y = player->world_pos.y / game->tile.height;
		player->is_moving = true;
	}
	return (1);
}

int	strafe_right(t_game *game)
{
	t_player *const	player = &game->player;
	const double	dx = cos(player->angle - M_PI_2) * player->speed;
	const double	dy = -sin(player->angle - M_PI_2) * player->speed;
	const t_vec2d	ori = player->world_pos;

	if (movable((t_vec2d){ori.x + dx, ori.y}, &game->map, game->tile, &game->door_states))
	{
		player->world_pos.x += dx;
		player->tile_index.x = player->world_pos.x / game->tile.width;
		player->is_moving = true;
	}
	if (movable((t_vec2d){ori.x, ori.y + dy}, &game->map, game->tile, &game->door_states))
	{
		player->world_pos.y += dy;
		player->tile_index.y = player->world_pos.y / game->tile.height;
		player->is_moving = true;
	}
	return (1);
}

int	open_door(t_game *game)
{
	const t_key			*m_key = &game->keystates.keys[KEY_SPACEBAR];
	static t_key_state	prev_m_key_state = NONE;

	if (!(prev_m_key_state & PRESS && m_key->state & RELEASE))
	{
		prev_m_key_state = m_key->state;
		return (0);
	}
	prev_m_key_state = m_key->state;
	t_player *const	player = &game->player;
	t_map	*const map = &game->map;
	const double	dx = player->direction.x * player->speed * 15;
	const double	dy = player->direction.y * player->speed * 15;
	const t_vec2d	ori = player->world_pos;

	t_door_states	*door_states = &game->door_states;
	t_vec2i	tile = {.x = (ori.x + dx) / game->tile.width,
		.y = (ori.y + dy) / game->tile.height};

	if (get_door(door_states, player->tile_index.x, player->tile_index.y)->is_door)
	{
		return (1);
	}
	t_door	*door = &door_states->doors[tile.y * map->width + tile.x];
	if (!door->is_door)
	{
		return (1);
	}
	door->is_closed = !door->is_closed;
	return (1);
}

