/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:55:13 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/25 22:08:30 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Doors.h"
#include "Game.h"
#include "libft.h"
#include "Utils.h"
#include <stdio.h>

t_door	init_door(void)
{
	t_door	door;
	
	door.is_door = true;
	door.is_closed = true;
	return (door);
}

t_door	*get_door(t_door_states *doors, int x, int y)
{
	return (&doors->doors[y * doors->map_width + x]);
}

int	count_doors(t_map *map)
{
	int	x;
	int	y;
	int	count;

	y = 0;
	count = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->layout[y][x] == 'D')
			{
				count++;
			}
			x++;
		}
		y++;
	}
	return (count);
}

t_door_states	init_doors(t_config *config, t_game *game)
{
	t_door_states	door_states;
	t_configurable	*element;
	int	i;

	i = 0;
	ft_bzero(&door_states, sizeof(door_states));

	while (i < MAX_CONFIGURABLE)
	{
		element = &config->configurables[i];
		if (ft_strcmp(element->type_identifier, "DOOR") == 0)
		{
			load_image(game, &door_states.img, element->line + element->value_offset);
			printf("LOAD %s!\n", element->line + element->value_offset);
			break ;
		}
		i++;
	}
	t_map	*map = &config->map;
	door_states.doors = xmalloc(sizeof (t_door) * (map->height * map->width));
	ft_bzero(door_states.doors, sizeof (t_door) * (map->height * map->width));
	door_states.map_width = map->width;
	door_states.door_count = count_doors(map);
	for (int y = 0; y < map->height; ++y)
	{
		for (int x = 0; x < map->width; ++x)
		{
			if (map->layout[y][x] == 'D')
			{
				door_states.doors[(y * map->width) + x] = init_door();
			}
		}
	}
	return (door_states);
}
