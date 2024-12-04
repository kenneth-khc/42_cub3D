/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:23:30 by kecheong          #+#    #+#             */
/*   Updated: 2024/12/04 20:56:58 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <mlx.h>
#include <string.h>
#include "Game.h"
#include "Map.h"
#include "Image.h"

#define MAP_WIDTH 10
#define MAP_HEIGHT 10

char	g_layout[MAP_HEIGHT][MAP_WIDTH] =
{
{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
{'1', 'E', '1', '0', '0', '0', '0', '0', '0', '1'},
{'1', '0', '0', '0', '0', '0', '0', '0', '1', '1'},
{'1', '0', '1', '0', '0', '0', '0', '1', '0', '1'},
{'1', '0', '0', '1', '0', '0', '1', '0', '0', '1'},
{'1', '1', '0', '0', '0', '1', '0', '0', '0', '1'},
{'1', '0', '0', '0', '1', '0', '0', '0', '0', '1'},
{'1', '1', '0', '1', '0', '0', '0', '0', '0', '1'},
{'1', '1', '1', '1', '0', '0', '0', '0', '0', '1'},
{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
};

void	init_map(t_map *map, t_game *game, t_player *player)
{
	extern char	g_layout[MAP_HEIGHT][MAP_WIDTH];

	// TODO: copy map dynamically instead
	(void)game;
	memcpy(&map->layout, g_layout, sizeof(g_layout));
	map->width = MAP_WIDTH;
	map->height = MAP_HEIGHT;
	map->player_pos = player->map_pos;
}

void	print_map(char layout[10][10])
{
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			printf("%c ", layout[y][x]);
		}
		printf("\n");
	}
}

void	update_map(t_map *map, t_player *player)
{
	const t_vector_int	old_pos = map->player_pos;
	const t_vector_int	new_pos = player->map_pos;
	
	map->layout[old_pos.y][old_pos.x] = '0';
	map->layout[new_pos.y][new_pos.x] = 'P';
	map->player_pos = player->map_pos;
}
