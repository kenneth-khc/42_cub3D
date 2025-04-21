/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:36:16 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/22 03:47:45 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parse.h"
#include <unistd.h>
#include <fcntl.h>

t_config	parse(char *filename)
{
	int			fd;
	char		*line;
	t_config	config;

	config = init_blank_config();
	fd = open_file(filename);
	config.get_next_line = gnl_trim_whitespaces_skip_empty;
	line = config.get_next_line(fd);
	while (line)
	{
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
	pad_borders(&config.map);
	return (config);
}
