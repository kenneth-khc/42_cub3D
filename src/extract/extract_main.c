/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 12:19:36 by kytan             #+#    #+#             */
/*   Updated: 2025/04/18 12:20:34 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.h"

void	extract_main(t_parse *parser)
{
	extract_file_data(game.parser.fd, &game.parser);		// extracts
	validate_map_textures(parser->file_extract, parser);
	extract_map_data(parser->fd, parser);
}