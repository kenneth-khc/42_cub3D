/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:24:47 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/15 17:17:08 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "Vector.h"

enum e_cardinal_directions
{
	EAST = 0,
	NORTH = 1,
	WEST = 2,
	SOUTH = 3
};

typedef struct s_player
{
	int			start_direction; // player initialized to NO/SO/EA/WE
	double		angle;
	double		field_of_view;
	double		speed;
	t_vec2d		direction; // a normalized direction vector
	t_vec2i		tile_index; // position in the map/2D array
	t_vec2d		world_pos; // position in the game world, not the screen
	bool		is_moving;
	t_vec2d		delta;
}	t_player;

typedef struct s_game	t_game;

void	init_player(t_player *player);
void	update_player_position(t_player *player, t_vec2d new_pos,
			t_game *game);

#endif
