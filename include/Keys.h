/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:00:51 by kecheong          #+#    #+#             */
/*   Updated: 2024/12/04 20:04:46 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# include <stdbool.h>

enum e_events
{
	KEYPRESS_EVENT = 2,
	KEYRELEASE_EVENT = 3,
	MOUSEMOVE_EVENT = 6,
	ENTER_EVENT = 7 // event for when mouse enters the window
};

enum e_event_masks
{
	KEYPRESS_MASK = 1L << 0,
	KEYRELEASE_MASK = 1L << 1,
	ENTER_WINDOW_MASK = 1L << 4,
	POINTER_MOTION_MASK = 1L << 6
};

# if defined(__linux__)

enum e_mlx_keycodes
{
	MLX_KEY_W = 119,
	MLX_KEY_A = 97,
	MLX_KEY_S = 115,
	MLX_KEY_D = 100,
	MLX_KEY_LEFT = 65361,
	MLX_KEY_RIGHT = 65363,
	MLX_KEY_ESC = 65307,
	MLX_KEY_M = 109
};

# elif defined(__APPLE__)

enum e_mlx_keycodes
{
	MLX_KEY_W = 13,
	MLX_KEY_A = 0,
	MLX_KEY_S = 1,
	MLX_KEY_D = 2,
	MLX_KEY_LEFT = 123,
	MLX_KEY_RIGHT = 124,
	MLX_KEY_ESC = 53
};

# endif

enum e_keycodes
{
	KEY_W = 0,
	KEY_A = 1,
	KEY_S = 2,
	KEY_D = 3,
	KEY_LEFT = 4,
	KEY_RIGHT = 5,
	KEY_ESC = 6,
	KEY_M = 7
};

# define N_KEYS 8 // number of keys that we care about

typedef void			(*t_action)(void*);

/* A single key */
typedef struct	s_key
{
	int			mlx_keycode; // translate this into an idx into our keys array
	t_action	action; // a function that does something when a key is pressed
	bool		pressed; // whether the key is pressed or released
}	t_key;

/* Storing the state of all the keys we care about */
typedef struct s_keys
{
	t_key	keys[N_KEYS];
}	t_keys;

typedef struct s_game	t_game;
typedef struct s_player	t_player;

void	init_keybindings(t_keys *keys);
int		press_key(int keycode, t_game *game);
int		release_key(int keycode, t_game *game);
void	process_keys(t_keys *keys, t_game *game);

void	move_forward(void *ptr);
void	move_backward(void *ptr);
void	strafe_left(void *ptr);
void	strafe_right(void *ptr);

void	rotate_left(void *ptr);
void	rotate_right(void *ptr);

void	toggle_minimap(void *ptr);
void	close_game(void *ptr);

#endif
