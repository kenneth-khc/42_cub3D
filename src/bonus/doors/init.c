/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:55:13 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/26 05:23:22 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Doors.h"
#include "Utils.h"

static int		count_doors(const t_map *map);
static t_door	init_door(int x, int y);

t_doors	init_doors(const t_map *map)
{
	t_doors	doors;
	int		door_count;
	int		x;
	int		y;
	int		i;

	door_count = count_doors(map);
	doors.ptr = xmalloc(sizeof (t_door) * (door_count + 1));
	doors.ptr[door_count].tile_pos.x = -1;
	doors.ptr[door_count].tile_pos.y = -1;
	y = 1;
	i = 0;
	while (y < map->height)
	{
		x = 1;
		while (x < map->width)
		{
			if (map->layout[y][x] == 'D')
				doors.ptr[i++] = init_door(x, y);
			x++;
		}
		y++;
	}
	return (doors);
}

static t_door	init_door(int x, int y)
{
	t_door	door;

	door.tile_pos.x = x;
	door.tile_pos.y = y;
	door.is_closed = true;
	return (door);
}

static int	count_doors(const t_map *map)
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
