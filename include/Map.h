/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:14:59 by kecheong          #+#    #+#             */
/*   Updated: 2024/12/02 11:05:59 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "Image.h"
# include "Player.h"

typedef struct t_map
{
	char	layout[10][10];
	t_vec2i	player_pos;
	int		width;
	int		height;
	t_image	img; // mlx image used to display the map onto the screen
}	t_map;

struct	s_game;

void	init_map(t_map *map, struct s_game *game, t_player *player);
void	set_floors(t_map *map, t_player *player);
void	print_map(char layout[10][10]);
bool	collide(t_map *map, t_vec2d *world_pos, t_game *game);
bool	within_world_bounds(t_vec2d *pos, t_map *map, t_game *game);
bool	is_wall(t_map *map, int x, int y);
void	update_map(t_map *map, t_player *player);

#endif
