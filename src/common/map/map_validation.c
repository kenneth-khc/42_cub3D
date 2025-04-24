/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 00:45:25 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/22 03:39:43 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Map.h"
#include "Utils.h"

static void	validate_single_player(t_map *map, int x, int y);
static void	check_surrounding(const t_map *map, int x, int y);

void	validate_map(t_map *map)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	print_map(map);
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			c = map->layout[y][x];
			if (is_player(c))
			{
				validate_single_player(map, x, y);
			}
			if (is_floor(c))
			{
				check_surrounding(map, x, y);
			}
			x++;
		}
		y++;
	}
	return ;
}

/* Checks that there is only a single player character (N/S/E/W) encountered
 * within the map, and set that as the player_pos. If it is already set,
 * it means a duplicate was encountered. */
void	validate_single_player(t_map *map, int x, int y)
{
	if (map->player_pos.x == 0 && map->player_pos.y == 0)
	{
		map->player_pos.x = x;
		map->player_pos.y = y;
	}
	else
	{
		error("Duplicate player found.\n");
	}
}

/* Checks the surrounding 8 tiles and if any of them are an empty space,
 * our map is not considered surrounded
 *
 * eg:
 *
 * 111         11 1             111
 * 1N1 = OK    1N1  = NOT OK    1N1 0 = NOT OK
 * 111         111              111                 */
void	check_surrounding(const t_map *map, int x, int y)
{
	if (map->layout[y - 1][x - 1] == ' '
		|| map->layout[y - 1][x] == ' '
		|| map->layout[y - 1][x + 1] == ' '
		|| map->layout[y][x - 1] == ' '
		|| map->layout[y][x + 1] == ' '
		|| map->layout[y + 1][x - 1] == ' '
		|| map->layout[y + 1][x] == ' '
		|| map->layout[y + 1][x + 1] == ' ')
	{
		error("Map is not surrounded by walls completely\n");
	}
}
