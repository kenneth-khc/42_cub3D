/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:14:59 by kecheong          #+#    #+#             */
/*   Updated: 2024/11/01 15:33:58 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "Image.h"
# include "Player.h"

# define TILE_WIDTH 64.0
# define TILE_HEIGHT 64.0

typedef struct t_map
{
	char	layout[10][10];
	int		width;
	int		height;
	t_image	img; // the mlx image used to display the map onto the screen
}	t_map;

struct	s_game;

void	init_map(t_map *map, struct s_game *game);
void	clear_minimap(t_map *map);
void	set_floors(t_map *map, t_player *player);

#endif
