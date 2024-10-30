/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:24:47 by kecheong          #+#    #+#             */
/*   Updated: 2024/10/30 12:41:14 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "Vector.h"

enum e_Cardinal_Directions
{
	EAST = 0,
	NORTH = 1,
	WEST = 2,
	SOUTH = 3
};

typedef struct s_Player
{
	int			start_direction; // player initialized to NO/SO/EA/WE
	double		angle_in_radians;
	t_Vector	direction; // a normalized direction vector
	t_Vector	map_pos; // position in the map/2D array
	t_Vector	world_pos; // position in the game world, not the screen
}	t_Player;

void	init_player(t_Player *player);

#endif
