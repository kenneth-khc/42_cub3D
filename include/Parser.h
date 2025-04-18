/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:34:07 by kytan             #+#    #+#             */
/*   Updated: 2025/04/18 12:10:29 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define TOTAL_TEXTURES 6


typedef struct s_parse			t_parse;

/**
 * @struct s_parse
 * @brief A structure that contains data for parsing and validating.
 *
 * @var s_parse::fd
 * Member 'fd' is the file descriptor of input file
 *
 * @var s_parse::raw_data
 * Member 'raw_data' represents the data read from the input file stored as a single string
 *
 * @var s_parse::file_extract
 * Member 'file_extract' represents the extracted input file stored as a char ** array
 *
 *  * @var s_parse::map_extract
 * Member 'map_extract' represents the extracted map layout information stored as a char ** array
 *
 * @var s_parse::map_textures
 * Member 'map_textures' is the container to store map textures in a char **array
 *
 *  * @var s_parse::map_layout
 * Member 'map_textures' is the container to store map layout in a 2D char ** array
 *
 * @var s_parse::breakpoint_idx
 * Member 'breakpoint_idx' is an index representing the breakpoint between the map textures section and the map layout section in the input file
 *
 * @var s_parse::map_width
 * Member 'map_width' represents the length of map width
 *
 * @var s_parse::map_depth
 * Member 'map_depth' represents the lenth og map depth
 *
 * @var s_parse::north_boundary_idx
 * Member 'north_boundary_idx' is the index of the map's north-most boundary wall
 *
 * @var s_parse::south_boundary_idx
 * Member 'south_boundary_idx' is the index of the map's south-most boundary wall
 *
 * @var s_parse::east_boundary_idx
 * Member 'east_boundary_idx' is the index of the map's east-most boundary wall
 *
 * @var s_parse::west_boundary_idx
 * Member 'west_boundary_idx' is the index of the map's west-most boundary wall
 *
 */
typedef struct s_parse
{
	char	**map_textures;	// {"./textures/west", "./textures/north", "./textures/east", "./textures/south"}
	char	**map_layout;		// parsed map layout stored as a 2D char **array

	/* FILE INFO & FILE EXTRACTS */
	int		fd;
	char	*raw_data;			// return of extract_map_data() stored as char ** array
	char	**file_extract;			// return of extract_file_data() stored as char ** array
	char	**map_extract;			// return of extract_map_data() stored as char ** array

	/* MAP INFO FOR FORMATTING N CLEANUP */
	int		breakpoint_idx;
	size_t		map_width;
	size_t		map_depth;

	int		north_boundary_idx;
	int		south_boundary_idx;
	int		east_boundary_idx;
	int		west_boundary_idx;
}	t_parse;

void	welcome_msg();

