/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elements_map.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:47:09 by kytan             #+#    #+#             */
/*   Updated: 2025/03/22 14:59:50 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Exit.h"
#include "libft.h"

/**
 * @brief Checks for invalid map characters
 *
 * Map characters consists of '0', '1', '(space)'.
 * Player characters consists of 'N', 'S', 'E', 'W'.
 * @return For invalid map characters, return `1`. Else, return `0`.
 */
static int	invalid_map_char(char **data)
{
	int		i;
	int		j;
	char	*string;

	i = -1;
	string = "01 NSEW";
	while (data[++i])
	{
		j = -1;
		while (data[i][++j])
			if (!ft_strchr(string, data[i][j]))
				return (1);
	}
	return (0);
}

void	check_rows(char **data)
{
	// GOAL: IF ENCLOSED_FLAG IS ON MEANS THE MAP CONTENT IS PROPERLY SURROUNDED

	// SKIP 1s UNTIL
	// IF "10"
	//		SET FLAG
	//		START LOOP
	//			SKIP 0S
	//		IF NOT 1
	//			RETURN INVALID -> THERES A SPACE IN THE MAP CONTENT OR THERES NO CLOSING
	// REPEAT


}


int	valid_map_integrity(char **file_data, t_game *game)
{
	;
}

void	validate_data_elements_map(char **file_data, t_game *game)
{
	char	**cleaned;

	file_data = file_data + game->parser.breakpoint_idx;
	if (!valid_map_integrity(file_data, game))
		exit_free("INVALID-ELEMENTS", game, 0);

	if (!valid_map_char(file_data, game))
		exit_free("INVALID-ELEMENTS", game, 0);

		// FORMAT MAP BY SKIPPING ANY SPACES
		cleaned = clean_format_map(file_data, game->parser.breakpoint_idx);
		if (!map)
			exit_free(parser);

		// USE BIT FLAG TO CHECK WALLS ARE SURROUNDED
		if (!valid_map_enclosure(map))
			exit_free(parser);

		// CHECK ALL 0s to hv TOP LEFT RIGHT BOTTOM TO BE NOT ' '
		if (!valid_map_content(map))
			exit_free(parser);

}

/**
 * 1. Invalid map characters [/]
 * 2. More than one player [/]
 * 3. Empty lines in between map content
 * 4. Map contente is not surrounded by walls
 * 5. Map content is not filled
 */
void	validate_data_elements_map(char **file_data, t_game *game)
{
	file_data = file_data + game->parser.breakpoint_idx;

	if (set_map_size(file_data, game))
		exit_free("INVALID-ELEMENTS", game, 0);

	if (invalid_map_char(file_data))
		exit_free("INVALID-ELEMENTS", game, 0);

	if (invalid_player(file_data))
		exit_free("INVALID-ELEMENTS", game, 0);

	if (invalid_walls(file_data))
		exit_free("INVALID-ELEMENTS", game, 0);

	if (invalid_interior(file_data))
		exit_free("INVALID-ELEMENTS", game, 0);



		char	**tmp_map;
		int		map_start;

		// CHECK FOR SKIPPED MAP ELEMENTS TO BE IN TACT + SET MAP START
	if (!valid_map_integrity(file_data, game))
		exit_free("INVALID-ELEMENTS", game, 0);

		// CHECK FOR INVALID MAP CHARACTERS
	if (!valid_map_char(file_data, game))
		exit_free("INVALID-ELEMENTS", game, 0);

		// FORMAT MAP BY SKIPPING ANY SPACES
		tmp_map = format_map(file_data, map_start);
		if (!map)
			exit_free(parser);

		// USE BIT FLAG TO CHECK WALLS ARE SURROUNDED
		if (!valid_map_enclosure(map))
			exit_free(parser);

		// CHECK ALL 0s to hv TOP LEFT RIGHT BOTTOM TO BE NOT ' '
		if (!valid_map_content(map))
			exit_free(parser);

}

/*
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
*/

/*static int	set_map_size(char **data, t_game *game)
{
	int		i;

	i = -1;
	while (data[++i])
	{

	}
}





static int	invalid_walls(char **data)
{
	wall_recursion(data, size, );
	if (end of row OR end of col)
		return ;
	if (wall_char)
	{
		check_top_char if not first row
			wall_side++
		check_bottom_char if not last row
			wall_side++
		check_left_char if not first col
			wall_side++
		check_right_char if not last col
			wall_side++
		if wall_side != 2
			exit_free();
		start_recursion to next wall character
	}
}

static int	invalid_interior(char **data)
{
	;
}*/
/*
int	check_rows(char **data)
{
	int		i;
	int		j;
	char	*map_ptr;

	i = -1;
	while (data[++i])
	{
		map_ptr = ft_strtrim(data[i], " ");
		if (!map_ptr)
			return (1);
		j = 0;
		// if (map_ptr[j] != '1')
		// 	return (1);
		while (map_ptr[j] == '1')
			if (map_ptr[j + 1] && map_ptr[j + 1] == '0')
				set flag;
				while (map_ptr[j] == '')
			j++;
		free(map_ptr);


		// ft_strchr(data[i])
		// while (data[i][++j])
		// {
		// 	while (isspace(data[i][j]))
		// 		data[i]++;
		// 	if (data[i][j] == '1')
		// 	{
		// 		if (!data[i][j + 1] || data[i][j + 1] != '0')
		// 			return (1);
		// 		if (data[i][j])
		// 				;
		// 	}
		// }
		free(line)
	}
}*/