/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 23:09:02 by kytan             #+#    #+#             */
/*   Updated: 2025/04/16 16:09:44 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/**
 * @brief Initializes all members of `parser`
 */
void	init_parser(t_parse *parser)
{
	parser->fd = -1;
	parser->file_extract = 0;
	parser->map_extract = 0;
	parser->raw_data = 0;
	parser->map_textures = 0;
	parser->map_layout = 0;
	parser->map_width = 0;
	parser->map_depth = 0;
	parser->breakpoint_idx = 0;
	parser->north_boundary_idx = 0;
	parser->south_boundary_idx = 0;
	parser->east_boundary_idx = 0;
	parser->west_boundary_idx = 0;
}
