/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:49:27 by kytan             #+#    #+#             */
/*   Updated: 2025/03/13 13:16:54 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.h"
#include "Validate.h"
#include "Game.h"
#include "libft.h"

void	init_parser(t_game *game)
{
	t_parse		parser;

	parser = game->parser;
	parser.data_file = 0;
	parser.data_textures = 0;
	parser.data_map = 0;
	parser.breakpoint_idx = -1;
	parser.map_width = 0;
	parser.map_height = 0;
}

void	start_parser(t_game *game, char *cub_file)
{
	t_parse		*parser;

	parser = &game->parser;
	if (!cub_file)
		exit_free("INVALID-ARGS", game, 0);
	parse_file_data(cub_file, parser, game);
	validate_data_file(parser, game);					// TO-DO + SET BREAKPOINT INDEX
	parse_texture_data(parser->data_file, game);
	parse_map_data(parser->data_file, game);	// TO-DO

	find_breakpoint_idx(parser, game);				// PUT IN VALIDATION
}
