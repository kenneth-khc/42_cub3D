/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:41:02 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/23 01:25:36 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Player.h"
#include "Minimap.h"

void	update(t_game *game)
{
	if (game->minimap.display)
	{
		update_minimap(&game->minimap, game);
	}
}
