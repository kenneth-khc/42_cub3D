/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:23:30 by kecheong          #+#    #+#             */
/*   Updated: 2024/12/02 11:10:48 by kecheong         ###   ########.fr       */
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

void	init_map(t_map *map, t_game *game)
{
	extern char	g_layout[MAP_HEIGHT][MAP_WIDTH];

	// TODO: copy map dynamically instead
	(void)game;
	memcpy(&map->layout, g_layout, sizeof(g_layout));
	map->width = MAP_WIDTH;
	map->height = MAP_HEIGHT;
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
