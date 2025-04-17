/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 00:22:18 by kytan             #+#    #+#             */
/*   Updated: 2025/03/11 21:09:17 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Exit.h"


/**
 * @brief sets the breakpoint index, the line right after every
 * texture elements(6) has been registered
 *
 * @note breakpoint_idx = index of the line after
 */
void	find_breakpoint_idx(t_parse *parser, t_game *game)
{
	int		texture_flags;
	char	*id_token;
	int		i;

	i = -1;
	while (parser->data_file[++i])
	{
		if (empty_line(parser->data_file[i]))							// SKIP EMPTY LINE
			continue ;
		id_token = ft_strtok(parser->data_file[i], ' ');	// TOKENIZE
		if (!id_token)
			exit_free("MEMORY-ALLOC", game, 0);
		if (!valid_identifier(id_token))
			exit_free("INVALID-ELEMENTS", game, id_token);
		
	}
	if (!parser->data_file[i])
		exit_free("INVALID-ELEMENTS", game, 0);
	parser->breakpoint_idx = i;
}