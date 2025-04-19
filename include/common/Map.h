/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:14:59 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/18 05:47:49 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "Image.h"
# include "Player.h"

typedef struct s_map
{
	/*char	layout[10][10];*/
	char	**layout;
	t_vec2i	player_pos;
	int		width;
	int		height;
	/*t_image	img; // mlx image used to display the map onto the screen*/
}	t_map;

struct	s_game;
struct	s_config;

void	init_map(t_map *map, struct s_config *config);
void	add_row(t_map *map, char *line);
void	set_floors(t_map *map, t_player *player);
void	print_map(char layout[10][10]);
bool	collide(t_map *map, t_vec2d *world_pos, t_dimensions *tile);
bool	within_world_bounds(t_vec2d *pos, t_map *map, t_dimensions *tile);
bool	is_wall(t_map *map, int x, int y);
void	update_map(t_map *map, t_player *player);

#endif
