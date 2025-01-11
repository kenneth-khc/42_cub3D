/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:46:37 by kecheong          #+#    #+#             */
/*   Updated: 2025/01/03 16:42:50 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "Game.h"
#include "Keys.h"

/* Translate MLX/X11 keycodes that we care about into something simpler
 * that we can work with
 * Reason: X11 keysyms go up to 5 digits, and we require an interface to store
 * and handle multiple keypresses at the same time, creating an array of size
 * 60k is a waste of space, so we only store keys that we actually use
 * Return -1 if it's not a key we care about */
int	translate_keycode(t_keystates *keystates, int mlx_keycode)
{
	int	keycode;

	keycode = 0;
	while (keycode < N_KEYS)
	{
		if (keystates->keys[keycode].mlx_keycode == mlx_keycode)
		{
			return (keycode);
		}
		keycode++;
	}
	return (-1);
}

/* When a key is pressed or released, we flip the state in our keys array
 * If it is not pressed, we now press it
 * If it is already pressed, we now release it */
int	press_release_key(int mlx_keycode, t_keystates *keystates)
{
	const int	keycode = translate_keycode(keystates, mlx_keycode);
	bool		pressed;

	if (keycode == -1)
	{
		return (-1);
	}
	else
	{
		pressed = keystates->keys[keycode].pressed;
		keystates->keys[keycode].pressed = !pressed;
		return (0);
	}
}

/* Go through the keys array, looking for keys that are pressed down, 
 * and call its associated function */
// TODO: is special handling required for diagonal movements? such as
// normalizing the movement vectors
void	process_keys(t_keystates *keystates, t_game *game)
{
	int	i;

	i = 0;
	while (i < N_KEYS)
	{
		if (keystates->keys[i].pressed)
		{
			keystates->keys[i].action(game);
		}
		i++;
	}
}
