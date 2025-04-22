/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:40:30 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/22 23:23:06 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "Player.h"
# include "Map.h"
# include "Raycaster.h"
# include "Keys.h"
# include "Renderer.h"
# include "Minimap.h"

typedef struct s_game
{
	// debugging purposes
	/*t_colours		colours;*/
	// end
	void			*mlx;
	void			*window;

	t_dimensions	screen;
	t_map			map;
	t_dimensions	tile; // width and height of 1 in game tile
	t_minimap		minimap;
	t_image			world_3d; // image of the game to be displayed
	t_player		player;
	t_raycaster		raycaster;
	t_renderer		renderer;
	t_keystates		keystates;
}	t_game;

void	init_game(t_game *game, t_config *config);
int		game_loop(t_game *game);
void	update(t_game *game);
int		process_mouse(int x, int y, void *param);

#endif
