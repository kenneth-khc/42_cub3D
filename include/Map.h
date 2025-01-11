/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:14:59 by kecheong          #+#    #+#             */
/*   Updated: 2025/01/11 10:18:13 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "Image.h"
# include "Player.h"

typedef struct t_map
{
	char			**layout;
	t_vec2i	player_pos;
	int				width;
	int				height;
	t_image			img; // mlx image used to display the map onto the screen
}	t_map;

struct	s_game;

void	init_map(t_map *map, struct s_game *game, t_player *player);
void	print_map(t_map *map, char **layout);
bool	collide(t_map *map, t_vec2d *world_pos, t_game *game);
bool	within_world_bounds(t_vec2d *pos, t_map *map, t_game *game);
bool	is_wall(t_map *map, int x, int y);
void	update_map(t_map *map, t_player *player);

#endif
