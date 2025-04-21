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

# include "Player.h"
# include "Vector.h"

typedef struct s_map
{
	int		width;
	int		height;
	char	**layout;
	t_vec2i	player_pos;
}	t_map;

struct	s_config;

void	init_map(t_map *map, struct s_config *config);
void	add_row(t_map *map, char *line);
void	print_map(t_map *map);
bool	collide(t_map *map, t_vec2d *world_pos, t_dimensions *tile);
bool	within_world_bounds(t_vec2d *pos, t_map *map, t_dimensions *tile);
bool	is_wall(t_map *map, int x, int y);
bool	is_whitespace(char c);
bool	is_player(char c);
bool	is_floor(char c);
void	pad_borders(t_map *map);

/* PROBABLY UNUSED */
# if 0
void	update_map(t_map *map, t_player *player);
# endif

#endif
