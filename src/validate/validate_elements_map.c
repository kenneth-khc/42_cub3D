/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elements_map.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:47:09 by kytan             #+#    #+#             */
/*   Updated: 2025/03/12 00:53:58 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Exit.h"
#include "libft.h"

int	invalid_player(char *element)
{
	int		player_ct;

	player_ct = 0;
	if (*element != 'N'
		&& *element != 'W'
		&& *element != 'S'
		&& *element != 'E')
		player_ct++;
	element++;
}

/**
 * @brief Checks for invalid map characters & if theres only 1 player
 *
 * Map characters consists of '0', '1', '(space)'.
 * Player characters consists of 'N', 'S', 'E', 'W'.
 * @return For invalid map characters, return `1`. Else, return `0`.
 */
int	invalid_map_char(char **data)
{
	int		i;
	int		j;
	char	*string;

	i = -1;
	string = "01 NSEWD";
	while (data[++i])
	{
		j = -1;
		while (data[i][++j])
			if (!ft_strchr(string, data[i][j]))
				return (1);
	}
	return (0);
}

/**
 * @brief Checks for invalid number of player
 *
 * @return For invalid .
 */
int	invalid_player(char **data)
{
	int		i;
	int		j;
	char	*string;
	int		player_ct;

	i = -1;
	string = "NSEW";
	player_ct = 0;
	while (data[++i])
	{
		j = -1;
		while (data[i][++j])
			if (ft_strchr(string, data[i][j]))
				player_ct++;
	}
	if (player_ct != 1)
		return (1);
	return (0);
}

int	invalid_walls(char **data)
{
	wall_recursion(data, size, );
	if (wall_char)
	{
		check_top_char if not first row
			wall_side++
		check_bottom_char if not last row
			wall_side++
		check_left_char if not first row
			wall_side++
		check_right_char if not last row
			wall_side++
		if wall_side != 2
			exit_free();
		start_recursion to next wall character
	}
}

void f_fill(char **tab, t_point size, char target, int row, int col)
{
	if (row < 0 || col < 0 || row >= size.y || col >= size.x)
		return;
	if (tab[row][col] == 'F' || tab[row][col] != target)
		return;
	tab[row][col] = 'F';

	f_fill(tab, size, target, row -1, col);
	f_fill(tab, size, target, row +1, col);
	f_fill(tab, size, target, row, col - 1);
	f_fill(tab, size, target, row, col + 1);
}

void  flood_fill(char **tab, t_point size, t_point begin)
{
	char target = tab[begin.y][begin.x];
	f_fill(tab, size, target, begin.y, begin.x);
}

void	validate_data_elements_map(char **file_data, t_game *game)
{
	file_data = file_data + game->parser.breakpoint_idx;
	if (invalid_map_char(file_data) || invalid_player(file_data))
		exit_free("INVALID-ELEMENTS", game, 0);
	if (invalid_walls(file_data))
		exit_free("INVALID-ELEMENTS", game, 0);
}
