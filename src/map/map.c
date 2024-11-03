/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:23:30 by kecheong          #+#    #+#             */
/*   Updated: 2024/11/01 15:33:09 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <string.h>
#include "Game.h"
#include "Map.h"
#include "Image.h"
#include "Player.h"

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

#define MINIMAP_GRID_WIDTH 20
#define MINIMAP_GRID_HEIGHT 20

void	clear_minimap(t_map *map)
{
	t_colour	white = {.value = 0x00FFFFFF};
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

void	set_floors(t_map *map, t_player *player)
{
	t_colour	black = {.value = 0x00000000};
	t_colour	cyan = {.s_component = {.alpha = 0x00, .red = 0x54, .green = 0x88, .blue = 0xf7}};
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
				// HACK: surely there is a better way to do this
				for (int yy = 0; yy < MINIMAP_GRID_HEIGHT - 1; yy++)
				{
					for (int xx = 0; xx < MINIMAP_GRID_WIDTH - 1; xx++)
					{
						*get_pixel_addr(&map->img,
							x * MINIMAP_GRID_WIDTH + xx,
							y * MINIMAP_GRID_HEIGHT + yy) = black.value;
					}
				}
			}
			// HACK: i shouldn't need to do this
			if (y == player->map_pos.y && x == player->map_pos.x)
			{
				for (int yy = MINIMAP_GRID_HEIGHT / 4;
					 yy < MINIMAP_GRID_HEIGHT - MINIMAP_GRID_HEIGHT / 4; yy++)
				{
					for (int xx = MINIMAP_GRID_WIDTH / 4;
						 xx < MINIMAP_GRID_WIDTH - MINIMAP_GRID_WIDTH / 4; xx++)
					{
						*get_pixel_addr(&map->img,
							x * MINIMAP_GRID_WIDTH + xx,
							y * MINIMAP_GRID_HEIGHT + yy) = cyan.value;
					}
				}
			}
			x++;
		}
		y++;
	}
}

// TODO: draw an actual field of view of the player on the map maybe
void	draw_field_of_view(t_map *map, t_player *player)
{
	(void)map; (void)player;
	/*t_colour		green = {.s_component = {.alpha = 0x00, .red = 0x00, .blue = 0x00, .green = 0xF0}};*/
	/*t_vector_int	start; */
	/*t_vector_int	end;*/
	/**/
	/*start = player->map_pos;*/
	/*end = (t_vector_int){.x = start.x * player->direction.x * 10, .y = start.y * player->direction.y * 10};*/
	/*draw_line_in_image(&map->img, player->map_pos, end, green);*/
}

void	init_map(t_map *map, t_game *game)
{
	extern char	g_layout[MAP_HEIGHT][MAP_WIDTH];

	// TODO: copy map dynamically instead
	memcpy(&map->layout, g_layout, sizeof(g_layout));
	map->width = MAP_WIDTH;
	map->height = MAP_HEIGHT;
	create_image(game->mlx, &map->img,
		map->width * MINIMAP_GRID_WIDTH,
		map->height * MINIMAP_GRID_HEIGHT);	

	clear_minimap(map);
	set_floors(map, &game->player);
	draw_field_of_view(map, &game->player);
}
