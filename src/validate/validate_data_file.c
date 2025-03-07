/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_data_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:49:45 by kytan             #+#    #+#             */
/*   Updated: 2025/03/07 18:22:07 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Exit.h"

void	validate_file_data(t_parse *parser, t_game *game)
{
	int		i;
	char	**data_file;

	i = -1;
	data_file = parser->data_file;
	while (data_file[++i] && textures_element_section)
	{
		;
	}
	while (data_file[i] && map_element_section)
	{
		// if not '1' and '0' then quit
		i++;
	}
	if (check textures filled && check map filled)
}

int	validate_file_data(char **file_data, t_game *game)
{
	int		i;
	int		txtr_flags;
	char	*token;

	i = -1;
	token = 0;
	txtr_flags  = 0;
	while (file_data[++i] && unfulfilled(txtr_flags))
	{
		if (empty_line(file_data[i]))
			continue ;
		token = ft_strtok(file_data[i], ' ');
		if (!token)
			exit_free("MEMORY-ALLOC", game, 0);
		else if (valid_identifier(token))
		{
			if (txtr_flags & (1 << id_idx(token)))
				exit_free("INVALID-ELEMENTS", game, token);
			txtr_flags ^= 1 << id_idx(token);
		}
		else
			return (exit_free(E_INVALID_MAP_ELEMENTS, cub, token));
	}
	return (1);
}