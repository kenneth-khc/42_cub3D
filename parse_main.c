/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 01:15:46 by kytan             #+#    #+#             */
/*   Updated: 2025/04/17 16:58:23 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	parse_main(t_parse *parser)
{
	validate_map_textures(parser->file_extract, parser);
	// validate_map_initial(parser);
	parse_map_textures(parser->file_extract, parser);
	extract_map_data(parser->fd, parser);
	parse_map_layout(parser->map_extract, parser);		// TO-DO: trim west and east white spaces, then create a 2d array with the new dups
	validate_map_layout(parser->map_extract, parser);
}
