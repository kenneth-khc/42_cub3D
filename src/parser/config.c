/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 04:54:17 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/17 06:09:56 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parse.h"
#include "libft.h"
#include "ft_dprintf.h"
#include <stdlib.h>
#include <stdio.h>

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
	config.configurables_complete = false;
	return (config);
}

void	set(t_configurable *element, char *line, size_t type_identifier_offset)
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
				set(element, line, type_identifier_offset);
				if (++config->configurables_completed == MAX_CONFIGURABLE)
				{
					config->configurables_complete = true;
					config->get_next_line = get_next_line_skip_empty_lines;
				}
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

void	parse_map_content(t_config *config, char *line)
{
	(void)config; (void)line;
}
