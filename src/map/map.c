/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:23:30 by kecheong          #+#    #+#             */
/*   Updated: 2024/10/30 15:34:03 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <string.h>
#include "Map.h"
#include "Image.h"

#define MAP_WIDTH 10
#define MAP_HEIGHT 10

char	g_layout[MAP_HEIGHT][MAP_WIDTH] =
{
{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
{'1', 'E', '0', '0', '0', '0', '0', '0', '0', '1'},
{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
};

#define MINIMAP_GRID_WIDTH 30
#define MINIMAP_GRID_HEIGHT 30

void	clear_minimap(t_Map *map)
{
	t_Colour	white = {.value = 0x00FFFFFF};
	int			y;
	int			x;
	
	y = 0;
	while (y < map->img.height)
	{
		x = 0;
		while (x < map->img.height)
		{
			*get_pixel_addr(&map->img, x, y) = white.value;
			x++;
		}
		y++;
	}
}

void	set_floors(t_Map *map)
{
	t_Colour	black = {.value = 0x00000000};
	int			y;
	int			x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->layout[y][x] != '1')
			{
				// TODO: surely there is a better way to do this
				for (int yy = 0; yy < MINIMAP_GRID_HEIGHT; yy++)
				{
					for (int xx = 0; xx < MINIMAP_GRID_WIDTH; xx++)
					{
						*get_pixel_addr(&map->img,
							x * MINIMAP_GRID_WIDTH + xx,
							y * MINIMAP_GRID_HEIGHT + yy) = black.value;
					}
				}
			}
			x++;
		}
		y++;
	}
}

void	init_map(t_Map *map, void *mlx)
{
	extern char	g_layout[MAP_HEIGHT][MAP_WIDTH];

	// TODO: copy map dynamically instead
	memcpy(&map->layout, g_layout, sizeof(g_layout));
	map->width = MAP_WIDTH;
	map->height = MAP_HEIGHT;
	create_image(mlx, &map->img,
		map->width * MINIMAP_GRID_WIDTH,
		map->height * MINIMAP_GRID_HEIGHT);	

	clear_minimap(map);
	set_floors(map);
}
