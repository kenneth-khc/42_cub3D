/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:24:47 by kecheong          #+#    #+#             */
/*   Updated: 2024/11/01 13:57:18 by kecheong         ###   ########.fr       */
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
	int				start_direction; // player initialized to NO/SO/EA/WE
	double			angle_in_radians;
	double			field_of_view;
	double			speed;
	t_vector_double	direction; // a normalized direction vector
	t_vector_int	map_pos; // position in the map/2D array
	t_vector_double	world_pos; // position in the game world, not the screen
}	t_player;

void	init_player(t_player *player);

#endif
