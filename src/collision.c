/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 01:53:56 by kecheong          #+#    #+#             */
/*   Updated: 2024/11/12 01:58:26 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Map.h"
#include "Vector.h"

extern char	g_layout[10][10];

bool	collide(t_map *map, t_vector_double *world_pos, t_game *game)
{
	(void)map;
	t_vector_int	pos;

	pos.x = world_pos->x / game->tile_width;
	pos.y = world_pos->y / game->tile_height;
	if (g_layout[pos.y][pos.x] == '1')
	{
		return (true);
	}
	else
	{
		return (false);
	}

}
