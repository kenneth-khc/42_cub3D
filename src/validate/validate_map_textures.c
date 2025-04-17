/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 01:37:29 by kytan             #+#    #+#             */
/*   Updated: 2025/04/16 05:35:43 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"

#define FULFILLED 63

void	validate_map_textures(char **file_extract, t_parse *parser)
{
	int		i;
	char	*token;
	int		txtr_flags;

	i = -1;
	token = 0;
	txtr_flags  = 0;
	while (file_extract[++i] && txtr_flags != FULFILLED)
	{
		if (empty_line(file_extract[i]))
			continue ;
		token = ft_strtok(file_extract[i], ' ');
		if (!token)
			exit_free("MEMORY-ALLOC", parser, 0);
		if (!valid_identifier(token))
			exit_free("INVALID-ELEMENTS-00", parser, token);
		if (txtr_flags & (1 << id_idx(token, parser)))
			exit_free("INVALID-ELEMENTS-01", parser, token);
		txtr_flags ^= 1 << id_idx(token, parser);
		free(token);
	}
	if (txtr_flags != FULFILLED)
	{
		printBinary(txtr_flags);
		printBinary(FULFILLED);
		exit_free("INVALID-ELEMENTS-02", parser, 0);
	}
	parser->breakpoint_idx = i;
}
