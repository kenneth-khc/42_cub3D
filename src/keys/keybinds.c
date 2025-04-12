/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 20:04:34 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/13 02:02:38 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "Game.h"
#include "Keys.h"
#include "Minimap.h"
#include "mlx.h"

static void	look_up(void *game, t_key*);
static void	look_down(void *game, t_key*);

//TODO: generalize and refactor movement/rotation functions if possible

/* Map a given mlx keycode to a function to be fired when pressed */
t_key	map_key(int interested, enum e_mlx_keycodes keycode, t_action action)
{
	t_key	new_keybinding;

	new_keybinding.mlx_keycode = keycode;
	new_keybinding.action = action;
	new_keybinding.state = NONE;
	new_keybinding.interested = interested;
	return (new_keybinding);
}

void	init_keybindings(t_keystates *keystates)
{
	keystates->keys[KEY_W] = map_key(PRESS, MLX_KEY_W, move_forward);
	keystates->keys[KEY_A] = map_key(PRESS, MLX_KEY_A, strafe_left);
	keystates->keys[KEY_S] = map_key(PRESS, MLX_KEY_S, move_backward);
	keystates->keys[KEY_D] = map_key(PRESS, MLX_KEY_D, strafe_right);
	keystates->keys[KEY_LEFT] = map_key(PRESS, MLX_KEY_LEFT, rotate_left);
	keystates->keys[KEY_RIGHT] = map_key(PRESS, MLX_KEY_RIGHT, rotate_right);
	keystates->keys[KEY_ESC] = map_key(RELEASE, MLX_KEY_ESC, close_game);
	keystates->keys[KEY_M] = map_key(PRESS | RELEASE, MLX_KEY_M, toggle_minimap);
	keystates->keys[KEY_UP] = map_key(PRESS, MLX_KEY_UP, look_up);
	keystates->keys[KEY_DOWN] = map_key(PRESS, MLX_KEY_DOWN, look_down);
}

void	look_up(void *ptr, t_key* key)
{
	(void)key;
	t_game *const	game = (t_game *)ptr;
	const int		upper_bound = game->screen.height - game->screen.height / 4;

	if (game->renderer.midpoint < upper_bound)
		game->renderer.midpoint += 5;
}

void	look_down(void *ptr, t_key* key)
{
	(void)key;
	t_game *const	game = (t_game *)ptr;
	const int		lower_bound = game->screen.height / 4;

	if (game->renderer.midpoint > lower_bound)
		game->renderer.midpoint -= 5;
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
void	rotate_left(void *ptr, t_key* key)
{
	(void)key;
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

void	rotate_right(void *ptr, t_key* key)
{
	(void)key;
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

void	toggle_minimap(void *ptr, t_key* key)
{
	t_game *const		game = (t_game *)ptr;
	t_minimap *const	minimap = &game->minimap;
	static int			previous_state = 0;

	if (previous_state & PRESS && key->state & RELEASE)
	{
		minimap->display = !minimap->display;
	}
	previous_state = key->state;
}

void	close_game(void *ptr, t_key* key)
{
	(void)key;
	t_game *const	game = (t_game*)ptr;

	mlx_destroy_image(game->mlx, game->minimap.img.instance);
	mlx_destroy_image(game->mlx, game->world_3d.instance);
	mlx_destroy_image(game->mlx, game->renderer.textures[0].instance);
	mlx_destroy_image(game->mlx, game->renderer.textures[1].instance);
	mlx_destroy_image(game->mlx, game->renderer.textures[2].instance);
	mlx_destroy_image(game->mlx, game->renderer.textures[3].instance);
	mlx_destroy_window(game->mlx, game->window);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
}
