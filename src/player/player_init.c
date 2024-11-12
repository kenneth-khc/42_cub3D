/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:17:27 by kecheong          #+#    #+#             */
/*   Updated: 2024/10/30 23:05:06 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "Player.h"
#include "Utils.h"
#include "Map.h"

void	init_player(t_player *player)
{
	player->start_direction = EAST;
	if (player->start_direction == EAST)
	{
		player->angle_in_radians = degrees_to_radians(0);
	}
	else if (player->start_direction == NORTH)
	{
		player->angle_in_radians = degrees_to_radians(90);
	}
	else if (player->start_direction == WEST)
	{
		player->angle_in_radians = degrees_to_radians(180);
	}
	else
	{
		player->angle_in_radians = degrees_to_radians(270);
	}
	player->direction.x = cos(player->angle_in_radians);
	player->direction.y = -sin(player->angle_in_radians);
	// FIX: hardcoded
	player->field_of_view = degrees_to_radians(10);
	player->map_pos.y = 1;
	player->map_pos.x = 1;
	// pos in the world, player should spawn in the center of a square so we
	// add half of the tile size
	player->world_pos.x = 1 * 64 + (TILE_WIDTH / 2);
	player->world_pos.y = 1 * 64 + (TILE_HEIGHT / 2);
	player->speed = 2.0;
}
