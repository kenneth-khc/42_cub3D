/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:11:39 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/13 02:02:42 by kecheong         ###   ########.fr       */
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
 * D - strafe player to the rihgt (move in -90 degrees)
 */

void	move_forward(void *ptr, t_key *key)
{
	(void)key;
	t_game *const	game = (t_game *)ptr;
	t_player *const	player = &game->player;
	t_map *const	map = &game->map;
	t_vec2d	test;
	bool			collision;

	test.x = player->world_pos.x + player->direction.x * player->speed;
	test.y = player->world_pos.y + player->direction.y * player->speed;
	collision = collide(map, &test, game)
		|| !within_world_bounds(&test, map, game);
	if (!collision)
	{
		update_player_position(player, test, game);
		update_map(map, player);
		update_minimap(&game->minimap, game);
	}
}

void	move_backward(void *ptr, t_key *key)
{
	(void)key;
	t_game *const	game = (t_game *)ptr;
	t_player *const	player = &game->player;
	t_map *const	map = &game->map;
	t_vec2d	test;
	bool			collision;

	test.x = player->world_pos.x + -player->direction.x * player->speed;
	test.y = player->world_pos.y + -player->direction.y * player->speed;
	collision = collide(map, &test, game)
		|| !within_world_bounds(&test, map, game);
	if (!collision)
	{
		update_player_position(player, test, game);
		update_map(map, player);
		update_minimap(&game->minimap, game);
	}
}

void	strafe_left(void *ptr, t_key *key)
{
	(void)key;
	t_game *const	game = (t_game *)ptr;
	t_player *const	player = &game->player;
	t_map *const	map = &game->map;
	t_vec2d	test;
	bool			collision;

	test.x = player->world_pos.x
		+ cos(player->angle_in_radians + M_PI / 2) * player->speed;
	test.y = player->world_pos.y
		+ -sin(player->angle_in_radians + M_PI / 2) * player->speed;
	collision = collide(map, &test, game)
		|| !within_world_bounds(&test, map, game);
	if (!collision)
	{
		update_player_position(player, test, game);
		update_map(map, player);
		update_minimap(&game->minimap, game);
	}
}

void	strafe_right(void *ptr, t_key *key)
{
	(void)key;
	t_game *const	game = (t_game *)ptr;
	t_player *const	player = &game->player;
	t_map *const	map = &game->map;
	t_vec2d	test;
	bool			collision;

	test.x = player->world_pos.x
		+ cos(player->angle_in_radians - M_PI / 2) * player->speed;
	test.y = player->world_pos.y
		+ -sin(player->angle_in_radians - M_PI / 2) * player->speed;
	collision = collide(map, &test, game)
		|| !within_world_bounds(&test, map, game);
	if (!collision)
	{
		update_player_position(player, test, game);
		update_map(map, player);
		update_minimap(&game->minimap, game);
	}
}
