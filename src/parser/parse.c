/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:36:16 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/17 06:10:36 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parse.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void	parse(char *filename)
{
	int			fd;
	char		*line;
	t_config	config;

	printf("Filename: %s\n", filename);
	config = init_blank_config();
	fd = open_file(filename);
	config.get_next_line = get_next_line_trim_whitespaces;
	line = config.get_next_line(fd);
	while (line)
	{
		printf("|%s|\n", line);
		if (!config.configurables_complete)
		{
			validate_element(&config, line);
		}
		else
		{
			config.get_next_line = get_next_line_trim_newline;
			parse_map_content(&config, line);
		}
		line = config.get_next_line(fd);
	}
}
