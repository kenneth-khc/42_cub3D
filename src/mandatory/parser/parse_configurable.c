/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_configurable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 06:03:12 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/26 09:13:06 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parse.h"
#include "libft.h"
#include "ft_dprintf.h"
#include <stdlib.h>

#define MAX_CONFIGURABLE 6

static char	*extract_type_identifier(char *line);

const char	*validate_type_identifier(char *line)
{
	const static char	*valid_identifiers[MAX_CONFIGURABLE] = {
		"NO", "SO", "WE", "EA", "F", "C"
	};
	const char			*valid_identifier;
	char				*test_identifier;
	int					i;

	i = 0;
	test_identifier = extract_type_identifier(line);
	while (i < MAX_CONFIGURABLE)
	{
		valid_identifier = valid_identifiers[i];
		if (ft_strcmp(valid_identifier, test_identifier) == 0)
		{
			free(test_identifier);
			return (valid_identifier);
		}
		i++;
	}
	ft_dprintf(STDERR_FILENO, "Invalid type identifier `%s`\n",
		test_identifier);
	free(test_identifier);
	exit(1);
}

static char	*extract_type_identifier(char *line)
{
	int	offset;

	offset = 0;
	while (line[offset])
	{
		if (is_whitespace(line[offset]))
		{
			break ;
		}
		offset++;
	}
	return (ft_substr(line, 0, offset));
}
