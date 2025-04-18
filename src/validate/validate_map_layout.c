/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_layout.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 12:23:44 by kytan             #+#    #+#             */
/*   Updated: 2025/04/18 12:48:30 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.h"
#include "libft.h"

#define VALID 1
#define INVALID 0

void	validate_map_characters(char **map_layout, t_parse *parser)
{
	int		i;
	int		j;
	char	*char_set;

	i = -1;
	char_set = " 01NSEW";
	while (map_layout[++i])
	{
		j = -1;
		while (map_layout[i][++j])
			if (!ft_strchr(char_set, map_layout[i][j]))
				exit_free("INVALID CHARACTERS", parser, 0);
	}
}

void	validate_map_player_ct(char **map_layout, t_parse *parser)
{
	int		i;
	int		j;
	char	*char_set;
	int		player_ct;

	i = -1;
	player_ct = 0;
	char_set = "NSEW";
	while (map_layout[++i])
	{
		j = -1;
		while (map_layout[i][++j])
			if (ft_strchr(char_set, map_layout[i][j]))
				player_ct++;
	}
	if (player_ct != 1)
		exit_free("INVALID PLAYER", parser, 0);
}

/**
 * @return VALID(1) is surrounding walls are valid. INVALID(0) if invalid.
 */
int	valid_surrounding_walls(char**map_layout, int i, int j, t_parse *parser)
{
	if (j != parser->west_boundary_idx)
	{
		if (map_layout[i][j - 1] != '0' || map_layout[i][j - 1] != '1')
			return (INVALID);
	}
	if (j != parser->east_boundary_idx)
	{
		if (map_layout[i][j + 1] != '0' || map_layout[i][j + 1] != '1')
			return (INVALID);
	}
	if (i !=  parser->north_boundary_idx)
	{
		if (map_layout[i - 1][j] != '0' || map_layout[i - 1][j] != '1')
			return (INVALID);
	}
	if (i !=  parser->south_boundary_idx)
	{
		if (map_layout[i + 1][j] != '0' || map_layout[i + 1][j] != '1')
			return (INVALID);
	}
}

void	validate_map_interior(char**map_layout, t_parse *parser)
{
	int		i;
	int		j;

	i = -1;
	while (map_layout[i])
	{
		j = -1;
		while (map_layout[i][++j])
		{
			if (map_layout[i][j] == '0')
			{
				if (!valid_surrounding_walls(map_layout, i, j))
					exit_free("INVALID MAP", parser, 0);
			}
		}
	}
}

/**
 * @brief Validates the parsed map layout
 *
 * Validates map characters.
 * Validates player count.
 * Validates map interior.
 */
void	validate_map_layout(char **map_layout, t_parse *parser)
{
	validate_map_characters(map_layout, parser);
	validate_map_player_ct(map_layout, parser);
	validate_map_interior(map_layout, parser);
}