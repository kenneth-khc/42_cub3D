/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 01:15:46 by kytan             #+#    #+#             */
/*   Updated: 2025/04/18 12:25:22 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.h"

void	parse_main(t_parse *parser)
{
	parse_map_textures(parser->file_extract, parser);
	parse_map_layout(parser->map_extract, parser);		// TO-DO: trim west and east white spaces, then create a 2d array with the new dups
	validate_map_layout(parser->map_layout, parser);
}
