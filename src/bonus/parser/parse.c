/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:36:16 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/26 06:03:20 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parse.h"
#include "Utils.h"
#include "libft.h"
#include "ft_dprintf.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

t_config	parse(char *filename)
{
	int			fd;
	char		*line;
	t_config	config;

	config = init_blank_config();
	fd = open_file(filename);
	config.get_next_line = gnl_trim_whitespaces_skip_empty;
	line = config.get_next_line(fd);
	if (line == NULL)
		error("File is empty\n");
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

void	validate_element(t_config *config, char *line)
{
	int				i;
	char			*type_identifier;
	size_t			type_identifier_offset;
	t_configurable	*element;

	i = 0;
	type_identifier_offset = identify_type_identifier(line, &type_identifier);
	if (type_identifier == NULL)
		error("Invalid type identifier\n");
	while (i < MAX_CONFIGURABLE)
	{
		element = &config->configurables[i];
		if (ft_strcmp(type_identifier, element->type_identifier) == 0)
		{
			if (element->identifier_offset == 0 && element->value_offset == 0)
			{
				set(element, config, line, type_identifier_offset);
				return ;
			}
			else
				error("Duplicate value for element\n");
		}
		i++;
	}
	error("Invalid type identifier\n");
}

static bool	is_valid_map_character_bonus(char c)
{
	return (c == ' ' || c == '0' || c == '1'
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'D');
}

void	parse_map_content(t_config *config, char *line)
{
	size_t			i;
	const size_t	line_len = ft_strlen(line);

	i = 0;
	while (i < line_len)
	{
		if (!is_valid_map_character_bonus(line[i]))
		{
			ft_dprintf(STDERR_FILENO, "Error\n""Invalid map character\n");
			exit(1);
		}
		i++;
	}
	add_row(&config->map, line);
}

size_t	identify_type_identifier(char *line, char **type_identifier)
{
	size_t	offset;

	offset = 0;
	while (line[offset] && is_whitespace(line[offset]))
	{
		offset++;
	}
	if (identified(&line[offset], "NO"))
		*type_identifier = "NO";
	else if (identified(&line[offset], "SO"))
		*type_identifier = "SO";
	else if (identified(&line[offset], "WE"))
		*type_identifier = "WE";
	else if (identified(&line[offset], "EA"))
		*type_identifier = "EA";
	else if (identified(&line[offset], "F"))
		*type_identifier = "F";
	else if (identified(&line[offset], "C"))
		*type_identifier = "C";
	else if (identified(&line[offset], "DOOR"))
		*type_identifier = "DOOR";
	else
		*type_identifier = NULL;
	return (offset);
}

bool	identified(const char *line, const char *identifier)
{
	const size_t	identifier_len = ft_strlen(identifier);
	size_t			i;

	i = 0;
	while (i < identifier_len)
	{
		if (line[i] != identifier[i])
		{
			return (false);
		}
		else
		{
			i++;
		}
	}
	return (true);
}
