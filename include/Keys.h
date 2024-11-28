/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:00:51 by kecheong          #+#    #+#             */
/*   Updated: 2024/11/15 22:43:49 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# include "Game.h"

enum e_events
{
	KEYPRESS_EVENT = 2,
	MOUSEMOVE_EVENT = 6,
	ENTER_EVENT = 7 // event for when mouse enters the window
};

enum e_event_masks
{
	KEYPRESS_MASK = 1L << 0,
	ENTER_WINDOW_MASK = 1L << 4,
	POINTER_MOTION_MASK = 1L << 6
};

# if defined(__linux__)

enum e_keys
{
	KEY_ESC = 65307,
	KEY_W = 119,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100,
	KEY_LEFT = 65361,
	KEY_RIGHT = 65363
};

# elif defined(__APPLE__)

enum e_keys
{
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_ESC = 53
};

# endif

int	process_key(int keycode, t_game *game);

#endif
