/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:40:30 by kecheong          #+#    #+#             */
/*   Updated: 2024/10/30 14:15:51 by kecheong         ###   ########.fr       */
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
	int			screen_width;
	int			screen_height;
	t_map		map;
	t_image		ceiling;
	t_image		floor;
	t_player	player;
	t_ray		rays[SCREEN_WIDTH];
}	t_game;

#endif
