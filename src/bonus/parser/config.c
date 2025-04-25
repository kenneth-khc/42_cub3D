/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 04:54:17 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/26 06:03:14 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.h"
#include "Parse.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

t_config	init_blank_config(void)
{
	t_config	config;

	config = (t_config){0};
	config.configurables[0].type_identifier = "NO";
	config.configurables[1].type_identifier = "SO";
	config.configurables[2].type_identifier = "EA";
	config.configurables[3].type_identifier = "WE";
	config.configurables[4].type_identifier = "F";
	config.configurables[5].type_identifier = "C";
	config.configurables[6].type_identifier = "DOOR";
	return (config);
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
	while (line[offset])
	{
		offset++;
	}
	element->value_len = offset - element->value_offset;
	if (++config->configurables_completed == MAX_CONFIGURABLE)
	{
		config->get_next_line = gnl_trim_newline_skip_empty;
	}
}
