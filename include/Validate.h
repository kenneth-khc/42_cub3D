/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Validate.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:30:27 by kytan             #+#    #+#             */
/*   Updated: 2025/04/19 15:54:16 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.h"
#define FULFILLED 63

void	validate_map_layout(char **map_layout, t_parse *parser);

void	validate_map_textures(char **file_extract, t_parse *parser);

int	valid_identifier(char *token);

int	id_idx(char *id_token, t_parse *parser);

int	empty_line(char *s);