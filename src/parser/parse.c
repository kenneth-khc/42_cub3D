/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:36:16 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/18 05:42:36 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parse.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "ft_dprintf.h"
#include "libft.h"
#include <stdlib.h>

t_config	parse(char *filename)
{
	int			fd;
	char		*line;
	t_config	config;

	printf("Filename: %s\n", filename);
	config = init_blank_config();
	fd = open_file(filename);
	config.get_next_line = gnl_trim_whitespaces_skip_empty;
	line = config.get_next_line(fd);
	while (line)
	{
		printf("|%s|\n", line);
		if (config.configurables_completed != MAX_CONFIGURABLE)
		{
			validate_element(&config, line);
		}
		else
		{
			config.get_next_line = gnl_trim_newline;
			parse_map_content(&config, line);
		}
		line = config.get_next_line(fd);
	}
	return (config);
}

bool	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

bool	validate_map(t_map *map)
{
	int	y;
	int	x;
	int	row_len;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		row_len = ft_strlen(map->layout[y]);
		while (x < row_len)
		{
			if (is_player(map->layout[y][x]))
			{
				if (map->player_pos.x == 0 && map->player_pos.y == 0)
				{
					map->player_pos.x = x;
					map->player_pos.y = y;
				}
				else
				{
					ft_dprintf(STDERR_FILENO, "Error\nDuplicate character found.\n");
					exit(1);
				}
			}
			x++;
		}
		y++;
	}
	return (true);
}

bool	validate_configurables(t_configurable *configurables)
{
	(void)configurables;
	return (true);
}
