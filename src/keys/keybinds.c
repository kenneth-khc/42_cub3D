/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 20:04:34 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/13 23:58:01 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Keys.h"

/* Associate each MLX keycode to our own key, hooking it to a function to be
 * called when the key is pressed and/or released */
void	init_keybindings(t_keystates *keystates)
{
	t_key *const	keys = keystates->keys;

	keys[KEY_W] = map_key(PRESS, MLX_KEY_W, move_forward);
	keys[KEY_A] = map_key(PRESS, MLX_KEY_A, strafe_left);
	keys[KEY_S] = map_key(PRESS, MLX_KEY_S, move_backward);
	keys[KEY_D] = map_key(PRESS, MLX_KEY_D, strafe_right);
	keys[KEY_LEFT] = map_key(PRESS, MLX_KEY_LEFT, rotate_left);
	keys[KEY_RIGHT] = map_key(PRESS, MLX_KEY_RIGHT, rotate_right);
	keys[KEY_ESC] = map_key(RELEASE, MLX_KEY_ESC, close_game);
	keys[KEY_M] = map_key(PRESS | RELEASE, MLX_KEY_M, toggle_minimap);
	keys[KEY_UP] = map_key(PRESS, MLX_KEY_UP, look_up);
	keys[KEY_DOWN] = map_key(PRESS, MLX_KEY_DOWN, look_down);
}

/* Create a new keybinding, with interest specifying the state of the key
 * to call the function (PRESS or RELEASE) */
t_key	map_key(int interest, enum e_mlx_keycodes mlx_keycode, t_action action)
{
	t_key	new_keybinding;

	new_keybinding.mlx_keycode = mlx_keycode;
	new_keybinding.action = action;
	new_keybinding.state = NONE;
	new_keybinding.interest = interest;
	return (new_keybinding);
}
