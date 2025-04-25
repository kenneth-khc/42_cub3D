/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:46:37 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/26 03:57:03 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Keys.h"
#include <stdbool.h>
#include <stddef.h>

/* Go through our keys, checking the state of each key, and call its associated
 * function if we are interested in that state */
void	process_keys(t_keystates *keystates, t_game *game)
{
	int		i;
	t_key	*key;

	i = 0;
	key = (t_key *){0};
	while (i < N_KEYS)
	{
		key = &keystates->keys[i];
		if (key->state & key->interest)
		{
			key->action(game);
		}
		i++;
	}
}

static int	translate_keycode(t_keystates *keystates, int mlx_keycode);

/* When a key is pressed or released, we flip the state in our keys array
 * If it is not pressed, we now press it
 * If it is already pressed, we now release it */
int	press_key(int mlx_keycode, t_keystates *keystates)
{
	t_key		*key;
	const int	keycode = translate_keycode(keystates, mlx_keycode);

	if (keycode == -1)
	{
		return (-1);
	}
	else
	{
		key = &keystates->keys[keycode];
		key->state = PRESS;
		return (0);
	}
}

int	release_key(int mlx_keycode, t_keystates *keystates)
{
	t_key		*key;
	const int	keycode = translate_keycode(keystates, mlx_keycode);

	if (keycode == -1)
	{
		return (-1);
	}
	else
	{
		key = &keystates->keys[keycode];
		key->state = RELEASE;
		return (0);
	}
}

/* Translate MLX/X11 keycodes that we care about into something simpler
 * that we can work with
 * Reason: X11 keysyms go up to 5 digits, and we require an interface to store
 * and handle multiple keypresses at the same time, creating an array of size
 * 60k is a waste of space, so we only store keys that we actually use
 * Return -1 if it's not a key we care about */
int	translate_keycode(t_keystates *keystates, int mlx_keycode)
{
	int		i;
	t_key	*key;

	i = 0;
	key = NULL;
	while (i < N_KEYS)
	{
		key = &keystates->keys[i];
		if (key->mlx_keycode == mlx_keycode)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

/* Store the previous states of each key, initialized to NONE by default.
 * When this gets called with a key, we check the previous stored state,
 * returning true if it was previously PRESSED and now RELEASED. */
bool	pressed_and_released(const t_key *key, enum e_keycodes keycode)
{
	static enum e_key_state	states[N_KEYS] = {NONE};

	if (states[keycode] & PRESS && key->state & RELEASE)
	{
		states[keycode] = key->state;
		return (true);
	}
	else
	{
		states[keycode] = key->state;
		return (false);
	}
}
