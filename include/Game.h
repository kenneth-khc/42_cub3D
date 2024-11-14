/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:40:30 by kecheong          #+#    #+#             */
/*   Updated: 2024/11/14 18:23:38 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# ifndef SCREEN_WIDTH
#  define SCREEN_WIDTH 1000
# endif
# ifndef SCREEN_HEIGHT
#  define SCREEN_HEIGHT 1000
# endif

# include "Player.h"
# include "Map.h"
# include "Minimap.h"
# include "Raycaster.h"

# include <stdio.h>

typedef struct s_game
{
	// debugging purposes
	FILE		*logfile;
	t_colours	colours;
	// end

	void		*mlx;
	void		*window;
	int			screen_width; // width of the screen of the game
	int			screen_height; // height of the screen of the game
	t_map		map; // minimap
	double		tile_width; // width of 1 in-game tile
	double		tile_height; // height of 1 in-game tile
	t_minimap	minimap;
	/*t_image		world2D;*/
	t_image		world_3d; // image of the game to be displayed
	t_player	player;
	t_raycaster	raycaster;
}	t_game;

void	init_minimap(t_game *game, t_map *map, t_minimap *minimap);

#endif
