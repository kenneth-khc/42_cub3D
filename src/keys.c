/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:46:37 by kecheong          #+#    #+#             */
/*   Updated: 2024/10/30 22:25:05 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#include "Keys.h"

bool	is_movement_key(int keycode)
{
	return (keycode == KEY_W
			|| keycode == KEY_A
			|| keycode == KEY_S
			|| keycode == KEY_D);
}

/*void	move_player(int keycode, t_player *player, t_game *game)*/
/*{*/
/*	int	dx;*/
/*	int	dy;*/
/**/
/*	dx = 0;*/
/*	dy = 0;*/
/*	if (keycode == KEY_W)*/
/*	{*/
/*		dx = 0;*/
/*		dy = -1;*/
/*	}*/
/*}*/

extern char g_layout[10][10];
// TODO: use parsed map instead of global map
int	process_key(int keycode, t_game *game)
{
	t_player	*player = &game->player;
	t_map		*map = &game->map; (void)map;

	if (keycode == KEY_ESC)
	{
		exit(0);
		return (0);
	}
	if (keycode == KEY_LEFT) // turn left
	{
		printf("turning left\n");
		player->angle_in_radians += 0.1;
		if (radians_to_degrees(player->angle_in_radians) > 360)
		{
			player->angle_in_radians -= degrees_to_radians(360);
		}
		player->direction.x = cos(game->player.angle_in_radians);
		player->direction.y = -sin(game->player.angle_in_radians);
	}
	else if (keycode == KEY_RIGHT) // turn right
	{
		printf("turning right\n");
		player->angle_in_radians -= 0.1;
		if (radians_to_degrees(player->angle_in_radians < 0))
		{
			player->angle_in_radians += degrees_to_radians(360);
		}
		player->direction.x = cos(game->player.angle_in_radians);
		player->direction.y = -sin(game->player.angle_in_radians);
	}
	// TODO: move properly, ideally implement diagonals too
	g_layout[player->map_pos.y][player->map_pos.x] = '0';
	if (keycode == KEY_W) // move up
	{
		printf("Player MapX: %d MapY: %d\n", player->map_pos.x, player->map_pos.y);
		printf("Player WPosX: %f WPosY: %f\n", player->world_pos.x, player->world_pos.y);
		printf("Moving...\n");
		player->world_pos.y += player->direction.y * player->speed;
		player->world_pos.x += player->direction.x * player->speed;
		g_layout[player->map_pos.y][player->map_pos.x] = 'E';
		printf("Player MapX: %d MapY: %d\n", player->map_pos.x, player->map_pos.y);
		printf("Player WPosX: %f WPosY: %f\n", player->world_pos.x, player->world_pos.y);
	}
	else if (keycode == KEY_S) // move back
	{
		player->world_pos.y -= player->direction.y * player->speed;
		player->world_pos.x -= player->direction.x * player->speed;
	}
	else if (keycode == KEY_A)
	{

	}
	else if (keycode == KEY_D)
	{

	}
	else // TODO: hook into other keys rather than just moving
	{
		return (0);
	}
	player->map_pos.y = player->world_pos.y / game->tile_height;
	player->map_pos.x = player->world_pos.x / game->tile_width;
	g_layout[player->map_pos.y][player->map_pos.x] = 'E';
	return (0);
}

