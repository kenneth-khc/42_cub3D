/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 20:04:34 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/22 06:37:22 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Keys.h"
#include "libft.h"

/* Associate each MLX keycode to our own key, hooking it to a function to be
 * called when the key is pressed and/or released */
t_keystates	init_keybindings(void)
{
	t_keystates		keystates;
	t_key *const	keys = keystates.keys;

	ft_bzero(&keystates, sizeof(keystates));
	keys[KEY_W] = map_key(PRESS, MLX_KEY_W, move_forward);
	keys[KEY_A] = map_key(PRESS, MLX_KEY_A, strafe_left);
	keys[KEY_S] = map_key(PRESS, MLX_KEY_S, move_backward);
	keys[KEY_D] = map_key(PRESS, MLX_KEY_D, strafe_right);
	keys[KEY_LEFT] = map_key(PRESS, MLX_KEY_LEFT, rotate_left);
	keys[KEY_RIGHT] = map_key(PRESS, MLX_KEY_RIGHT, rotate_right);
	keys[KEY_ESC] = map_key(RELEASE, MLX_KEY_ESC, close_game);
	keys[KEY_UP] = map_key(PRESS, MLX_KEY_UP, look_up);
	keys[KEY_DOWN] = map_key(PRESS, MLX_KEY_DOWN, look_down);
	return (keystates);
}
