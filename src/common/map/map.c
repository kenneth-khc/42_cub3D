/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:23:30 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/22 04:31:19 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Map.h"
#include "Parse.h"
#include "Utils.h"
#include "libft.h"
#include <mlx.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Copy the map from the config into a map in our running game */
void	init_map(t_map *map, t_config *config)
{
	map->width = config->map.width;
	map->height = config->map.height;
	map->layout = config->map.layout;
	map->player_pos = config->map.player_pos;
}

/* Adds a row into the layout by reallocating enough space and copying it
 * over from an old layout */
void	add_row(t_map *map, char *line)
{
	int				i;
	char **const	before_realloc = map->layout;
	const size_t	row_len = ft_strlen(line);

	if ((int)row_len > map->width)
	{
		map->width = row_len;
	}
	map->height++;
	map->layout = malloc(sizeof(char *) * map->height);
	if (map->layout == NULL)
	{
		error("out of memory\n");
	}
	i = 0;
	while (i < map->height - 1)
	{
		map->layout[i] = before_realloc[i];
		i++;
	}
	map->layout[map->height - 1] = line;
	free(before_realloc);
}

/* Print the 2D map, replacing spaces with - for visualization */
void	print_map(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->layout[y][x] == ' ')
			{
				printf("- ");
			}
			else
			{
				printf("%c ", map->layout[y][x]);
			}
			x++;
		}
		printf("\n");
		y++;
	}
}

/* PROBABLY UNUSED */
#if 0

void	update_map(t_map *map, t_player *player)
{
	const t_vec2i	old_pos = map->player_pos;
	const t_vec2i	new_pos = player->tile_index;

	map->layout[old_pos.y][old_pos.x] = '0';
	map->layout[new_pos.y][new_pos.x] = 'P';
	map->player_pos = player->tile_index;
}
#endif
