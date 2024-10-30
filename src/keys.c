/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:46:37 by kecheong          #+#    #+#             */
/*   Updated: 2024/10/30 22:25:05 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "Game.h"
#include "Keys.h"

bool	is_movement_key(int keycode)
{
	return (keycode == KEY_W
			|| keycode == KEY_A
			|| keycode == KEY_S
			|| keycode == KEY_D);
}

/*void	move_player(int keycode, t_player *player, t_game *game)*/
/*{*/
/*	int	dx;*/
/*	int	dy;*/
/**/
/*	dx = 0;*/
/*	dy = 0;*/
/*	if (keycode == KEY_W)*/
/*	{*/
/*		dx = 0;*/
/*		dy = -1;*/
/*	}*/
/*}*/

int	process_key(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		exit(0);
	}
	if (is_movement_key(keycode))
	{(void)game;
		/*move_player(keycode, &game->player, game);*/
	}
	return (0);
}

