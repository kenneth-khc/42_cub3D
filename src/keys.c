/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:46:37 by kecheong          #+#    #+#             */
/*   Updated: 2024/11/15 22:51:01 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#include "Vector.h"
#include "Keys.h"
#include "Map.h"
#include "Minimap.h"

/* Keys to be processed
 * For player movement, WASD is used
 * For rotating the camera, left and right arrow keys are used
 * For closing the game, ESC is used
 * Can be optimized further
 * maybe TODO: index into a keymap table and call its associated function rather
 *					than checking if elses :thinking:
 */
bool	is_movement_key(int keycode)
{
	return (keycode == KEY_W
			|| keycode == KEY_A
			|| keycode == KEY_S
			|| keycode == KEY_D);
}

bool	is_rotate_camera_key(int keycode)
{
	return (keycode == KEY_LEFT || keycode == KEY_RIGHT);
}

/* The player starts at a certain angle based on the input of the map.
 * (E)ast - 0 degrees | 0 or 2PI radians
 * (N)orth - 90 degrees | PI/2 radians
 * (W)est - 180 degrees | PI radians
 * (S)outh - 270 degrees | 3PI/2 radians
 *
 * By pressing the left arrow key, we increment the angle (going counterclockwise)
 * and the player's field of view moves to the left accordingly
 * By pressing the right arrow key, we decrement the angle causing it to go clockwise
 * and the field of view moves to the right accordingly
 * */
void	rotate_camera(t_player *player, int keycode)
{
	printf("Player ori direction: %f\n", radians_to_degrees(player->angle_in_radians));
	printf("Dir vector: %f %f\n", player->direction.x, player->direction.y);
	if (keycode == KEY_LEFT) // turn left
	{
		player->angle_in_radians += 0.1;
		if (radians_to_degrees(player->angle_in_radians) > 360)
		{
			player->angle_in_radians -= degrees_to_radians(360);
		}
		player->direction.x = cos(player->angle_in_radians);
		player->direction.y = -sin(player->angle_in_radians);
	}
	else if (keycode == KEY_RIGHT) // turn right
	{
		player->angle_in_radians -= 0.1;
		if (radians_to_degrees(player->angle_in_radians < 0))
		{
			player->angle_in_radians += degrees_to_radians(360);
		}
		player->direction.x = cos(player->angle_in_radians);
		player->direction.y = -sin(player->angle_in_radians);
	}
	printf("Player new direction: %f\n", radians_to_degrees(player->angle_in_radians));
	printf("Dir vector: %f %f\n\n", player->direction.x, player->direction.y);
}

void	move_player(t_player *player, int keycode, t_game *game, t_map *map)
{
	t_vector_double	test;
	// TODO: move properly, ideally implement diagonals too
	// TODO: refactor this garbage
	printf("Player ori pos: %f %f\n", player->world_pos.x, player->world_pos.y);
	if (keycode == KEY_W) // move up
	{
		test.x = player->world_pos.x + player->direction.x * player->speed;
		test.y = player->world_pos.y + player->direction.y * player->speed;
		if (!collide(&game->map, &test, game)
			&& within_world_bounds(&test, map, game))
		{
			map->layout[player->map_pos.y][player->map_pos.x] = '0';
			player->world_pos.x = test.x;
			player->world_pos.y = test.y;
			player->map_pos.x = player->world_pos.x / game->tile_width;
			player->map_pos.y = player->world_pos.y / game->tile_height;
			map->layout[player->map_pos.y][player->map_pos.x] = 'E';
			update_minimap(&game->minimap, game);
		}
	}
	else if (keycode == KEY_S) // move back
	{
		test.x = player->world_pos.x + -player->direction.x * player->speed;
		test.y = player->world_pos.y + -player->direction.y * player->speed;
		if (!collide(&game->map, &test, game)
			&& within_world_bounds(&test, map, game))
		{
			map->layout[player->map_pos.y][player->map_pos.x] = '0';
			player->world_pos.x = test.x;
			player->world_pos.y = test.y;
			player->map_pos.x = player->world_pos.x / game->tile_width;
			player->map_pos.y = player->world_pos.y / game->tile_height;
			map->layout[player->map_pos.y][player->map_pos.x] = 'E';
			update_minimap(&game->minimap, game);
		}
	}
	else if (keycode == KEY_A)
	{
		test.x = player->world_pos.x + cos(player->angle_in_radians + M_PI / 2) * player->speed;
		test.y = player->world_pos.y + -sin(player->angle_in_radians + M_PI / 2) * player->speed;
		if (!collide(&game->map, &test, game)
			&& within_world_bounds(&test, map, game))
		{
			map->layout[player->map_pos.y][player->map_pos.x] = '0';
			player->world_pos.x = test.x;
			player->world_pos.y = test.y;
			player->map_pos.x = player->world_pos.x / game->tile_width;
			player->map_pos.y = player->world_pos.y / game->tile_height;
			map->layout[player->map_pos.y][player->map_pos.x] = 'E';
			update_minimap(&game->minimap, game);
		}
	}
	else if (keycode == KEY_D)
	{
		test.x = player->world_pos.x + cos(player->angle_in_radians - M_PI / 2) * player->speed;
		test.y = player->world_pos.y + -sin(player->angle_in_radians - M_PI / 2) * player->speed;
		if (!collide(&game->map, &test, game)
			&& within_world_bounds(&test, map, game))
		{
			map->layout[player->map_pos.y][player->map_pos.x] = '0';
			player->world_pos.x = test.x;
			player->world_pos.y = test.y;
			player->map_pos.x = player->world_pos.x / game->tile_width;
			player->map_pos.y = player->world_pos.y / game->tile_height;
			map->layout[player->map_pos.y][player->map_pos.x] = 'E';
			update_minimap(&game->minimap, game);
		}
	}
	printf("Player new pos: %f %f\n\n", player->world_pos.x, player->world_pos.y);
	print_map(map->layout);
}

// TODO: use parsed map instead of global map
int	process_key(int keycode, t_game *game)
{
	t_player	*player = &game->player;
	t_map		*map = &game->map; (void)map;

	if (keycode == KEY_ESC)
	{
		exit(0);
	}
	else if (is_rotate_camera_key(keycode))
	{
		rotate_camera(player, keycode);
		update_minimap(&game->minimap, game);
	}
	else if (is_movement_key(keycode))
	{
		move_player(player, keycode, game, map);
	}
	return (0);
}

