/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:40:30 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/19 15:45:04 by kytan            ###   ########.fr       */
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
# include "Keys.h"
# include "Renderer.h"
# include "Parser.h"

# include <stdio.h>

typedef struct s_game
{
	// debugging purposes
	FILE			*logfile;
	t_colours		colours;
	// end
	void			*mlx;
	void			*window;

	t_dimensions	screen;
	t_map			map;
	double			tile_width; // width of 1 in-game tile
	double			tile_height; // height of 1 in-game tile
	t_minimap		minimap;
	/*t_image		world2D;*/
	t_image			world_3d; // image of the game to be displayed
	t_player		player;
	t_raycaster		raycaster;
	t_renderer		renderer;
	t_keystates		keystates;
	t_parse				parser;
}	t_game;

void	init_game(t_game *game);
void	init_minimap(t_game *game, t_map *map, t_minimap *minimap);
void	init_renderer(t_renderer *renderer, t_game *game,
			t_image *world, t_dimensions screen);
int		game_loop(t_game *game);
int		process_mouse(int x, int y, void *param);
void	welcome_msg();

#endif
