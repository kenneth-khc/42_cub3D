/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:01:13 by kytan             #+#    #+#             */
/*   Updated: 2025/04/19 05:32:09 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.h"
#include "libft.h"

#define TOTAL_TEXTURES 6

/**
 * @return If texture paths are not filled, return 0. Else, return 1.
 */
static int	filled_textures(char **texture_paths)
{
	int		i;

	i = 0;
	while (i < 6)
	{
		if (!texture_paths[i] == NULL)
			return (0);
		i++;
	}
	return (1);
}

void	parse_map_textures(char **file_extract, t_parse *parser)
{
	int					i;
	char				**texture_paths;
	char				*id_token;

	i = -1;
	texture_paths = ft_calloc(TOTAL_TEXTURES + 1, sizeof(char *));
	if (!texture_paths)
		exit_free("MEMORY-ALLOC", parser, 0);
	while (file_extract[++i] && !filled_textures(texture_paths))
	{
		if (empty_line(file_extract[i]))
			continue ;
		id_token = ft_strtok(file_extract[i], ' ');
		if (!id_token)
			exit_free("MEMORY-ALLOC", parser, 0);
		if (!valid_identifier(id_token))
			exit_free("INVALID-ELEMENTS-04", parser, id_token);
		if (!texture_paths[id_idx(id_token, parser)])
			texture_paths[id_idx(id_token, parser)] = ft_strtok(0, ' ');
		else
			exit_free("INVALID-ELEMENTS-05", parser, 0);
		free(id_token);
	}
	parser->map_textures = texture_paths;
}
