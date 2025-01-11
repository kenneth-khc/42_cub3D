/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:23:30 by kecheong          #+#    #+#             */
/*   Updated: 2025/01/11 10:31:26 by kytan            ###   ########.fr       */
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
	map->width = find_map_width();
	map->height = find_map_height();


	map->player_pos = player->tile_index;
}

void	print_map(t_map *map, char **layout)
{
	for (int y = 0; y < map->height; y++)
	{
		for (int x = 0; x < map->width; x++)
		{
			printf("%c ", layout[y][x]);
		}
		printf("\n");
	}
}

void	update_map(t_map *map, t_player *player)
{
	const t_vec2i	old_pos = map->player_pos;
	const t_vec2i	new_pos = player->tile_index;
	
	map->layout[old_pos.y][old_pos.x] = '0';
	map->layout[new_pos.y][new_pos.x] = 'P';
	map->player_pos = player->tile_index;
}
