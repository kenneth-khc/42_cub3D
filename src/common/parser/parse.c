/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:36:16 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/26 09:12:42 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parse.h"
#include "Config.h"
#include "Utils.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

t_config	parse(char *filename)
{
	t_config	config;
	int			fd;
	char		*line;

	ft_bzero(&config, sizeof(config));
	fd = open_file(filename);
	config.get_next_line = gnl_trim_whitespaces_skip_empty;
	line = config.get_next_line(fd);
	if (line == NULL)
		error("File is empty\n", NULL);
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
	const char		*type_identifier = validate_type_identifier(line);
	t_configurable	*element;

	i = 0;
	while (i < MAX_CONFIGURABLE)
	{
		element = &config->configurables[i];
		if (element->type_identifier
			&& ft_strcmp(type_identifier, element->type_identifier) == 0)
		{
			error("Duplicate", type_identifier);
		}
		else if (element->value_offset == 0)
		{
			*element = set(type_identifier, line);
			if (++config->configurables_completed == MAX_CONFIGURABLE)
				config->get_next_line = gnl_trim_newline_skip_empty;
			return ;
		}
		i++;
	}
	error("Invalid type identifier", type_identifier);
}

t_configurable	set(const char *type_identifier, char *line)
{
	t_configurable	element;
	size_t			offset;

	element.line = line;
	element.type_identifier = type_identifier;
	element.identifier_offset = 0;
	element.identifier_len = ft_strlen(type_identifier);
	offset = element.identifier_offset + element.identifier_len;
	while (line[offset] && is_whitespace(line[offset]))
	{
		offset++;
	}
	element.value_offset = offset;
	while (line[offset])
	{
		offset++;
	}
	element.value_len = offset - element.value_offset;
	return (element);
}

void	destroy_config(t_config *config)
{
	int	i;

	i = 0;
	while (i < MAX_CONFIGURABLE)
	{
		free(config->configurables[i].line);
		i++;
	}
}
