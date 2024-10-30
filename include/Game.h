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

typedef struct s_Game
{
	void		*mlx;
	void		*window;
	int			screen_width;
	int			screen_height;
	t_Map		map;
	t_Player	player;
}	t_Game;

#endif
