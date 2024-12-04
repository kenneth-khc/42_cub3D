/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 20:04:34 by kecheong          #+#    #+#             */
/*   Updated: 2024/12/04 22:03:29 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "Game.h"
#include "Keys.h"
#include "Minimap.h"

//TODO: generalize and refactor movement/rotation functions if possible

void	init_keybindings(t_keys *keys)
{
	keys->keys[KEY_W] = (t_key){MLX_KEY_W, move_forward, false};
	keys->keys[KEY_A] = (t_key){MLX_KEY_A, strafe_left, false};
	keys->keys[KEY_S] = (t_key){MLX_KEY_S, move_backward, false};
	keys->keys[KEY_D] = (t_key){MLX_KEY_D, strafe_right, false};
	keys->keys[KEY_LEFT] = (t_key){MLX_KEY_LEFT, rotate_left, false};
	keys->keys[KEY_RIGHT] = (t_key){MLX_KEY_RIGHT, rotate_right, false};
	keys->keys[KEY_ESC] = (t_key){MLX_KEY_ESC, close_game, false};
	keys->keys[KEY_M] = (t_key){MLX_KEY_M, toggle_minimap, false};
}

/* The player starts at a certain angle based on the input of the map.
 * (E)ast - 0 degrees | 0 or 2PI radians
 * (N)orth - 90 degrees | PI/2 radians
 * (W)est - 180 degrees | PI radians
 * (S)outh - 270 degrees | 3PI/2 radians
 *
 * By pressing the left arrow key, increment the angle (going counterclockwise)
 * and the player's field of view moves to the left accordingly
 * By pressing the right arrow key, decrement the angle (going clockwise)
 * and the field of view moves to the right accordingly
 * */
void	rotate_left(void *ptr)
{
	t_game *const	game = (t_game *)ptr;
	t_player *const	player = &game->player;

	player->angle_in_radians += 0.1;
	if (radians_to_degrees(player->angle_in_radians) > 360)
	{
		player->angle_in_radians -= degrees_to_radians(360);
	}
	player->direction.x = cos(player->angle_in_radians);
	player->direction.y = -sin(player->angle_in_radians);
	update_minimap(&game->minimap, game);
}

void	rotate_right(void *ptr)
{
	t_game *const	game = (t_game *)ptr;
	t_player *const	player = &game->player;

	player->angle_in_radians -= 0.1;
	if (radians_to_degrees(player->angle_in_radians < 0))
	{
		player->angle_in_radians += degrees_to_radians(360);
	}
	player->direction.x = cos(player->angle_in_radians);
	player->direction.y = -sin(player->angle_in_radians);
	update_minimap(&game->minimap, game);
}

void	close_game(void *ptr)
{
	(void)ptr;
	exit(0);
}

// TODO: this acts kinda weird probably because of how fast pressing/releasing
// is processed
// fix it so that it toggles properly
void	toggle_minimap(void *ptr)
{
	t_game *const		game = (t_game *)ptr;
	t_minimap *const	minimap = &game->minimap;

	minimap->display = !minimap->display;
}
