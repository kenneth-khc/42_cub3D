/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:23:30 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/18 05:47:54 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Map.h"
#include "Image.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <mlx.h>
#include <string.h>
#include "Parse.h"

#define MAP_WIDTH 10
#define MAP_HEIGHT 10

void	move(t_map *dst, t_map *src)
{
	int	i;

	i = 0;
	dst->layout = malloc(sizeof(char *) * src->height);
	if (!dst->layout)
	{
		exit(1);
	}
	while (i < src->height)
	{
		dst->layout[i] = src->layout[i];
		i++;
	}
	free(src->layout);
}

// TODO: use map from config file
void	init_map(t_map *map, t_config *config, t_game *game)
{
	(void)game;
	map->layout = config->map.layout;
	/*memcpy(&map->layout, layout, sizeof(layout));*/
	map->player_pos = config->map.player_pos;
	map->width = config->map.width;
	map->height = config->map.height;
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

void	add_row(t_map *map, char *line)
{
	int				i;
	char			**before_realloc;
	const size_t	row_len = ft_strlen(line);

	i = 0;
	if ((int)row_len > map->width)
	{
		map->width = row_len;
	}
	before_realloc = map->layout;
	map->height++;
	map->layout = malloc(sizeof(char *) * map->height);
	while (i < map->height - 1)
	{
		map->layout[i] = before_realloc[i];
		i++;
	}
	map->layout[map->height - 1] = line;
	free(before_realloc);
}
