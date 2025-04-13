/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:23:30 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/14 00:22:06 by kecheong         ###   ########.fr       */
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

// TODO: use map from config file
void	init_map(t_map *map, t_game *game, t_player *player)
{
	const char	layout[MAP_HEIGHT][MAP_WIDTH]
		= {
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

	(void)game;
	memcpy(&map->layout, layout, sizeof(layout));
	map->width = MAP_WIDTH;
	map->height = MAP_HEIGHT;
	map->player_pos = player->tile_index;
}

void	print_map(char layout[10][10])
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < MAP_HEIGHT)
	{
		while (x < MAP_WIDTH)
		{
			printf("%c ", layout[y][x]);
			x++;
		}
		printf("\n");
		y++;
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
