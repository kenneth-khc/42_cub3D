/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:17:27 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/23 01:12:01 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Settings.h"
#include "Player.h"
#include "Map.h"
#include "Utils.h"
#include <math.h>

static void	set_spawn_orientation(t_player *player, t_map *map);

t_player	init_player(t_map *map)
{
	t_player	player;

	player.tile_index.y = map->player_pos.y;
	player.tile_index.x = map->player_pos.x;
	player.world_pos.x = player.tile_index.x * TILE_WIDTH
		+ ((float)TILE_WIDTH / 2);
	player.world_pos.y = player.tile_index.y * TILE_HEIGHT
		+ ((float)TILE_HEIGHT / 2);
	set_spawn_orientation(&player, map);
	player.direction.x = cos(player.angle);
	player.direction.y = -sin(player.angle);
	player.field_of_view = radians(FIELD_OF_VIEW_ANGLE);
	player.speed = PLAYER_SPEED;
	return (player);
}

void	set_spawn_orientation(t_player *player, t_map *map)
{
	const int	x = player->tile_index.x;
	const int	y = player->tile_index.y;
	const char	player_character = map->layout[y][x];

	if (player_character == 'E')
	{
		player->angle = radians(0);
	}
	else if (player_character == 'N')
	{
		player->angle = radians(90);
	}
	else if (player_character == 'W')
	{
		player->angle = radians(180);
	}
	else
	{
		player->angle = radians(270);
	}
}
