/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:00:51 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/14 03:57:10 by kecheong         ###   ########.fr       */
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
	ENTER_EVENT = 7, // event for when mouse enters the window
	LEAVE_EVENT = 8
};

/* Event masks according to the MLX documentation */
enum e_event_masks
{
	KEYPRESS_MASK = 1L << 0,
	KEYRELEASE_MASK = 1L << 1,
	ENTER_WINDOW_MASK = 1L << 4,
	LEAVE_WINDOW_MASK = 1L << 5,
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
	MLX_KEY_UP = 65362,
	MLX_KEY_RIGHT = 65363,
	MLX_KEY_DOWN = 65364,
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
	KEY_M = 7,
	KEY_UP = 8,
	KEY_DOWN = 9
};

# define N_KEYS 10 // number of keys that we care about

typedef struct s_key	t_key;
typedef void			(*t_action)(void*);

typedef enum e_key_state
{
	NONE = 0b00,
	PRESS = 0b01,
	RELEASE = 0b10
}	t_key_state;

/* A single key */
typedef struct s_key
{
	int			mlx_keycode; // translate this into an idx into our keys array
	t_action	action; // a function that does something when a key is pressed
	t_key_state	state; // whether the key is pressed or release
	t_key_state	interest; // whether we are interested in PRESS and/or RELEASE
}	t_key;

/* Storing the state of all the keys we care about */
typedef struct s_keystates
{
	t_key	keys[N_KEYS];
}	t_keystates;

typedef struct s_game	t_game;
typedef struct s_player	t_player;

t_key	map_key(int interest, enum e_mlx_keycodes keycode, t_action action);
void	init_keybindings(t_keystates *keys);
int		press_release_key(int mlx_keycode, t_keystates *keys);
int		press_key(int mlx_keycode, t_keystates *keys);
int		release_key(int mlx_keycode, t_keystates *keys);
void	process_keys(t_keystates *keys, t_game *game);

void	look_up(void *game);
void	look_down(void *game);
void	move_forward(void *ptr);
void	move_backward(void *ptr);
void	strafe_left(void *ptr);
void	strafe_right(void *ptr);

void	rotate_left(void *ptr);
void	rotate_right(void *ptr);

void	toggle_minimap(void *ptr);
void	close_game(void *ptr);

#endif
