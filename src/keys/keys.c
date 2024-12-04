/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:46:37 by kecheong          #+#    #+#             */
/*   Updated: 2024/12/04 22:01:50 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "Game.h"
#include "Keys.h"

/* Translate MLX/X11 keycodes that we care about into something simpler
 * that we can work with
 * Reason: X11 keysyms go up to 5 digits, and we require an interface to store
 * and handle multiple keypresses at the same time, creating an array of size
 * 60k is a waste of space, so we only store what we care about */
int	translate_keycode(t_keys *keys, int mlx_keycode)
{
	int	keycode;

	keycode = 0;
	while (keycode < N_KEYS)
	{
		if (keys->keys[keycode].mlx_keycode == mlx_keycode)
		{
			return (keycode);
		}
		keycode++;
	}
	return (-1);
}

int	press_key(int mlx_keycode, t_game *game)
{
	const int	keycode = translate_keycode(&game->keys, mlx_keycode);

	if (keycode == -1)
	{
		return (-1);
	}
	else
	{
		game->keys.keys[keycode].pressed = true;
		return (0);
	}
}

int	release_key(int mlx_keycode, t_game *game)
{
	const int	keycode = translate_keycode(&game->keys, mlx_keycode);

	if (keycode == -1)
	{
		return (-1);
	}
	else
	{
		game->keys.keys[keycode].pressed = false;
		return (0);
	}
}

/* Go through the keys array, looking for keys that are pressed down, 
 * and call its associated function */
void	process_keys(t_keys *keys, t_game *game)
{
	int	i;

	i = 0;
	while (i < N_KEYS)
	{
		if (keys->keys[i].pressed)
		{
			keys->keys[i].action(game);
		}
		i++;
	}
}
