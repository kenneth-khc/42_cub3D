/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:19:50 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/26 09:20:06 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.h"
#include "Settings.h"

/* Move the player by dy and dx and calculate its new tile index within
 * the map */
void	move_player(t_player *player, double dx, double dy)
{
	player->world_pos.x += dx;
	player->world_pos.y += dy;
	player->tile_index.x = player->world_pos.x / TILE_WIDTH;
	player->tile_index.y = player->world_pos.y / TILE_HEIGHT;
	player->is_moving = true;
}
