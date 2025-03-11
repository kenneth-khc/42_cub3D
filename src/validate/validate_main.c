/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:49:45 by kytan             #+#    #+#             */
/*   Updated: 2025/03/11 23:47:36 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Validate.h"
#include "Exit.h"




/**
 * main validation for texture elements and map elements
 * sets the breakpoint index
 */
void	validate_data_file(t_parse *parser, t_game *game)
{
	validate_data_elements_textures(parser->data_file, game);
	validate_data_elements_map(parser->data_file, game);
}