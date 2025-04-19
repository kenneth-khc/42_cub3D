/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:17:27 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/18 05:44:13 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "Player.h"
#include "Utils.h"
#include "Game.h"
#include "Map.h"

#ifndef TILE_DIMENSIONS
# define TILE_DIMENSIONS
# define TILE_WIDTH 50
# define TILE_HEIGHT 50
#endif

static void	set_spawn_orientation(t_player *player, t_map *map);

// TODO: Initialize the player here depending on the config file
void	init_player(t_player *player, t_map *map)
{
	player->tile_index.y = map->player_pos.y;
	player->tile_index.x = map->player_pos.x;
	player->world_pos.x = player->tile_index.x * TILE_WIDTH
		+ ((float)TILE_WIDTH / 2);
	player->world_pos.y = player->tile_index.y * TILE_HEIGHT
		+ ((float)TILE_HEIGHT / 2);
	set_spawn_orientation(player, map);
	player->direction.x = cos(player->angle);
	player->direction.y = -sin(player->angle);
	player->field_of_view = degrees_to_radians(60);
	player->speed = 2.0;
	player->delta.x = 0;
	player->delta.y = 0;
}

void	set_spawn_orientation(t_player *player, t_map *map)
{
	const int	x = player->tile_index.x;
	const int	y = player->tile_index.y;
	const char	player_character = map->layout[y][x];

	if (player_character == 'E')
	{
		player->angle = degrees_to_radians(0);
	}
	else if (player_character == 'N')
	{
		player->angle = degrees_to_radians(90);
	}
	else if (player_character == 'W')
	{
		player->angle = degrees_to_radians(180);
	}
	else
	{
		player->angle = degrees_to_radians(270);
	}
}

void	update_player_position(t_player *player, t_vec2d new_pos,
		t_game *game)
{
	player->world_pos.x = new_pos.x;
	player->world_pos.y = new_pos.y;
	player->tile_index.x = new_pos.x / game->tile_width;
	player->tile_index.y = new_pos.y / game->tile_height;
}
