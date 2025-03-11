/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data_elements.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 23:50:32 by kytan             #+#    #+#             */
/*   Updated: 2025/03/12 01:02:00 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Validate.h"
#include "Exit.h"

void	parse_texture_data(char **data_file, t_game *game)
{
	;
}

void	parse_texture_data(char **data_file, t_game *game)
{
	int					i;
	char				**texture_paths;
	char				*id_token;

	i = -1;
	texture_paths = ft_calloc(TOTAL_TEXTURES + 1, sizeof(char *));
	if (!texture_paths)
		return (exit_free("MEMORY-ALLOC", game, 0));
	// print_texture_paths(texture_paths);
	while (data_file[++i])
	{
		if (empty_line(data_file[i]))
			continue ;
		id_token = ft_strtok(data_file[i], ' ');
		if (!id_token)
			exit_free("MEMORY-ALLOC", game, 0);
		if (!valid_identifier(id_token))
			exit_free("INVALID-ELEMENTS", game, id_token);
		if (!texture_paths[id_idx(id_token, game)])
			texture_paths[id_idx(id_token, game)] =
				valid_texture_path(ft_strtok(0, ' '));
		else
			exit_free("INVALID-ELEMENTS", game, data_file[i]);
		free(id_token);
	}
	game->parser.data_textures = texture_paths;
}
