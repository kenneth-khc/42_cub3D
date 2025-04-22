/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:41:02 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/24 02:28:28 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animation.h"
#include "Game.h"
#include "Player.h"
#include "Minimap.h"

void	update(t_game *game)
{
	t_player *const		player = &game->player;
	t_minimap *const	minimap = &game->minimap;
	t_renderer *const	renderer = &game->renderer;

	if (minimap->display)
	{
		update_minimap(minimap, &player->world_pos, game);
	}
	advance_animations(renderer, renderer->wall_animations);
}
