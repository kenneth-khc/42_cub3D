/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:11:39 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/13 21:09:02 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "Game.h"
#include "Vector.h"
#include "Player.h"
#include "Map.h"

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
	t_map *const	map = &game->map;
	t_vec2d			new_pos;
	bool			collision;

	new_pos.x = player->world_pos.x + player->direction.x * player->speed;
	new_pos.y = player->world_pos.y + player->direction.y * player->speed;
	collision = collide(map, &new_pos, game)
		|| !within_world_bounds(&new_pos, map, game);
	if (!collision)
	{
		update_player_position(player, new_pos, game);
		update_map(map, player);
		update_minimap(&game->minimap, game);
	}
}

void	move_backward(void *ptr)
{
	t_game *const	game = (t_game *)ptr;
	t_player *const	player = &game->player;
	t_map *const	map = &game->map;
	t_vec2d			new_pos;
	bool			collision;

	new_pos.x = player->world_pos.x + -player->direction.x * player->speed;
	new_pos.y = player->world_pos.y + -player->direction.y * player->speed;
	collision = collide(map, &new_pos, game)
		|| !within_world_bounds(&new_pos, map, game);
	if (!collision)
	{
		update_player_position(player, new_pos, game);
		update_map(map, player);
		update_minimap(&game->minimap, game);
	}
}

void	strafe_left(void *ptr)
{
	t_game *const	game = (t_game *)ptr;
	t_player *const	player = &game->player;
	t_map *const	map = &game->map;
	t_vec2d			new_pos;
	bool			collision;

	new_pos.x = player->world_pos.x
		+ cos(player->angle_in_radians + M_PI / 2) * player->speed;
	new_pos.y = player->world_pos.y
		+ -sin(player->angle_in_radians + M_PI / 2) * player->speed;
	collision = collide(map, &new_pos, game)
		|| !within_world_bounds(&new_pos, map, game);
	if (!collision)
	{
		update_player_position(player, new_pos, game);
		update_map(map, player);
		update_minimap(&game->minimap, game);
	}
}

void	strafe_right(void *ptr)
{
	t_game *const	game = (t_game *)ptr;
	t_player *const	player = &game->player;
	t_map *const	map = &game->map;
	t_vec2d			new_pos;
	bool			collision;

	new_pos.x = player->world_pos.x
		+ cos(player->angle_in_radians - M_PI / 2) * player->speed;
	new_pos.y = player->world_pos.y
		+ -sin(player->angle_in_radians - M_PI / 2) * player->speed;
	collision = collide(map, &new_pos, game)
		|| !within_world_bounds(&new_pos, map, game);
	if (!collision)
	{
		update_player_position(player, new_pos, game);
		update_map(map, player);
		update_minimap(&game->minimap, game);
	}
}
