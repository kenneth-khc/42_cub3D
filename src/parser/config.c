/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 04:54:17 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/18 05:36:24 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parse.h"
#include "libft.h"
#include "ft_dprintf.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

t_config	init_blank_config(void)
{
	t_config	config;

	ft_bzero(&config, sizeof(config));
	config.configurables[0].type_identifier = "NO";
	config.configurables[1].type_identifier = "SO";
	config.configurables[2].type_identifier = "EA";
	config.configurables[3].type_identifier = "WE";
	config.configurables[4].type_identifier = "F";
	config.configurables[5].type_identifier = "C";
	return (config);
}

void	set(t_configurable *element, t_config *config,
		char *line, size_t type_identifier_offset)
{
	size_t	offset;

	element->line = line;
	element->identifier_offset = type_identifier_offset;
	element->identifier_len = ft_strlen(element->type_identifier);
	offset = type_identifier_offset + element->identifier_len;
	while (line[offset] && is_whitespace(line[offset]))
	{
		offset++;
	}
	element->value_offset = offset;
	while (line[offset] && is_whitespace(line[offset]))
	{
		offset++;
	}
	element->value_len = offset - element->value_offset;
	if (++config->configurables_completed == MAX_CONFIGURABLE)
	{
		config->get_next_line = gnl_trim_newline_skip_empty;
	}
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
	{
		ft_dprintf(STDERR_FILENO, "Error\nInvalid type identifier\n");
		exit(1);
	}
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
			{
				ft_dprintf(STDERR_FILENO, "Error\nDuplicate value for element\n");
				exit(1);
			}
		}
		i++;
	}
	ft_dprintf(STDERR_FILENO, "Error\nInvalid type identifier\n");
	exit(1);
}

// TODO: prettify
// TODO: I rather if (condition) { expression } than if (condition) expression
size_t	identify_type_identifier(char *line, char **type_identifier)
{
	size_t	offset;

	offset = 0;
	while (line[offset] && is_whitespace(line[offset]))
		offset++;
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
	else
		*type_identifier = NULL;
	return (offset);
}
bool	is_valid_map_character(char c)
{
	return (c == ' ' || c == '0' || c == '1'
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	parse_map_content(t_config *config, char *line)
{
	size_t			i;
	const size_t	line_len = ft_strlen(line);

	i = 0;
	while (i < line_len)
	{
		if (!is_valid_map_character(line[i]))
		{
			ft_dprintf(STDERR_FILENO, "Error\n""Invalid map character\n");
			exit(1);
		}
		i++;
	}
	add_row(&config->map, line);
}
