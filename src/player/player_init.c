/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:17:27 by kecheong          #+#    #+#             */
/*   Updated: 2024/10/30 14:05:44 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "Player.h"

static double	degrees_to_radians(double degrees)
{
	return (degrees * M_PI / 180.0);
}

__unused static double	radians_to_degrees(double radians)
{
	return (radians * 180.0 / M_PI);
}

void	init_player(t_Player *player)
{
	player->start_direction = EAST;
	if (player->start_direction == EAST)
	{
		player->angle_in_radians = degrees_to_radians(0);
	}
	else if (player->start_direction == NORTH)
	{
		player->angle_in_radians = degrees_to_radians(90);
	}
	else if (player->start_direction == WEST)
	{
		player->angle_in_radians = degrees_to_radians(180);
	}
	else
	{
		player->angle_in_radians = degrees_to_radians(270);
	}
	player->direction.x = cos(player->angle_in_radians);
	player->direction.y = -sin(player->angle_in_radians);
}
