/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:40:30 by kecheong          #+#    #+#             */
/*   Updated: 2024/11/01 15:33:04 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "Player.h"
# include "Map.h"
# include "Raycaster.h"

#define SCREEN_WIDTH 1280

typedef struct s_game
{
	void		*mlx;
	void		*window;
	int			screen_width; // width of the screen of the game
	int			screen_height; // height of the screen of the game
	t_map		map; // minimap
	double		tile_width; // width of 1 in-game tile
	double		tile_height; // height of 1 in-game tile
	t_image		ceiling;
	t_image		floor;
	t_player	player;
	t_raycaster	raycaster;
}	t_game;

#endif
