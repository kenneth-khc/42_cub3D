/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_layout.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:24:20 by kytan             #+#    #+#             */
/*   Updated: 2025/04/19 05:32:21 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.h"
#include "libft.h"

void	parse_map_layout(char **map_extract, t_parse *parser)
{
	char		**map_layout;
	char		*map_line;
	int			i;
	size_t	copied;

	i = -1;

	map_layout = ft_calloc(parser->map_depth, sizeof(char *));
	if (map_layout)
		exit_free("MEMORY-ALLOC", parser, 0);
	while (map_extract[++i])
	{
		map_line = ft_calloc(parser->map_width + 1, sizeof(char));
		if (!map_line)
			exit_free("MEMORY-ALLOC", parser, map_layout);
		copied = ft_strlcpy(map_line,
			map_extract[i] + parser->west_boundary_idx,
			parser->map_width);
		map_layout[i] = map_line;
	}
	parser->map_layout = map_layout;
}

// int	find_map_legth(char **map_extract,  t_parse *parser)
// {
// 	int		i;

// 	i = 0;
// 	map_extract = map_extract + parser->breakpoint_idx;
// 	if (!map_extract || !map_extract[0])
// 		exit_free("INVALID ELEMENTS", parser, 0);
// 	while (empty_line(map_extract[i]))
// 		i++;
// 	while (map_extract[i])
// 		i++;
// 	return (i);
// }

// int	find_map_width(char **map_extract, t_parse *parser)
// {
// 	int		i;
// 	char	*line;
// 	size_t	line_length;

// 	i = -1;
// 	line = 0;
// 	line_length = 0;
// 	while (map_extract[++i])
// 	{
// 		line = ft_strtrim(map_extract[i], " ");
// 		if (!line)
// 			exit_free("MEMORY-ALLOC", parser, 0);
// 		if (line_length > ft_strlen(line))
// 			line_length = ft_strlen(line);
// 	}
// 	return (line_length);
// }


// int	find_first_idx(char **map_extract, t_parse *parser)
// {
// 	int	i;
// 	int	j;
// 	int	west_boundary_wall_idx;

// 	i = -1;
// 	if (!parser || !map_extract)
// 		exit_free("INVALID VALIDATION", parser, 0);
// 	west_boundary_wall_idx = -1;
// 	while (map_extract[++i])
// 	{
// 		j = -1;
// 		while (ft_isspace(map_extract[i][++j]))
// 			;
// 		if (j < west_boundary_wall_idx || west_boundary_wall_idx == -1)
// 			west_boundary_wall_idx = j;
// 	}
// 	return (west_boundary_wall_idx);
// }