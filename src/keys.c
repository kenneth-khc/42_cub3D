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

int	process_key(int keycode, t_game *game)
{
	t_player	*player = &game->player;
	t_map		*map = &game->map;
	if (keycode == KEY_ESC)
	{
		exit(0);
	}
	// TODO: move properly, ideally implement diagonals too
	if (keycode == KEY_W)
	{
		printf("forward\n");
		map->layout[player->map_pos.y][player->map_pos.x] = '0';
		player->world_pos.y -= player->direction.y * player->speed;
		player->map_pos.y = player->world_pos.y / game->tile_height;
		map->layout[player->map_pos.y][player->map_pos.x] = 'P';
	}
	else if (keycode == KEY_A)
	{
		printf("leftward\n");
		map->layout[player->map_pos.y][player->map_pos.x] = '0';
		player->world_pos.x -= player->direction.y * player->speed;
		player->map_pos.y = player->world_pos.y / game->tile_height;
		map->layout[player->map_pos.y][player->map_pos.x] = 'P';
	}
	else if (keycode == KEY_S)
	{
		printf("downward\n");
		map->layout[player->map_pos.y][player->map_pos.x] = '0';
		player->world_pos.y += player->direction.y * player->speed;
		player->map_pos.y = player->world_pos.y / game->tile_height;
		map->layout[player->map_pos.y][player->map_pos.x] = 'P';

	}
	else if (keycode == KEY_D)
	{
		printf("rightward\n");
		map->layout[player->map_pos.y][player->map_pos.x] = '0';
		player->world_pos.x += player->direction.y * player->speed;
		player->map_pos.y = player->world_pos.y / game->tile_height;
		map->layout[player->map_pos.y][player->map_pos.x] = 'P';
	}
	if (keycode == KEY_LEFT)
	{
		printf("turning left\n");
		player->angle_in_radians += 0.1;
		if (game->player.angle_in_radians < 0)
		{
			game->player.angle_in_radians += 2 * M_PI;
		}
		game->player.direction.x = cos(game->player.angle_in_radians);
		game->player.direction.y = -sin(game->player.angle_in_radians);
	}
	else if (keycode == KEY_RIGHT)
	{
		printf("turning right\n");
		player->angle_in_radians -= 0.1;
		if (game->player.angle_in_radians > 2 * M_PI)
		{
			game->player.angle_in_radians -= 2 * M_PI;
		}
		game->player.direction.x = cos(game->player.angle_in_radians);
		game->player.direction.y = -sin(game->player.angle_in_radians);
	}
	return (0);
}

