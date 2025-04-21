/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:41:02 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/22 05:41:21 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Player.h"
#include "Minimap.h"

void	update(t_game *game, t_player *player)
{
	if (player->is_moving)
	{
		player->world_pos.x += player->delta.x;
		player->world_pos.y += player->delta.y;
		player->tile_index.x = player->world_pos.x / game->tile.width;
		player->tile_index.y = player->world_pos.y / game->tile.height;
		player->is_moving = false;
		player->delta.x = 0;
		player->delta.y = 0;
	}
	if (game->minimap.display)
	{
		update_minimap(&game->minimap, game);
	}
}
