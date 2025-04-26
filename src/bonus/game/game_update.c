/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:41:02 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/24 06:06:54 by kecheong         ###   ########.fr       */
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
	renderer->wall_textures[NORTH]
		= *advance_frame(&renderer->wall_animations[NORTH]);
	renderer->wall_textures[WEST]
		= *advance_frame(&renderer->wall_animations[WEST]);
	renderer->wall_textures[EAST]
		= *advance_frame(&renderer->wall_animations[EAST]);
	renderer->wall_textures[SOUTH]
		= *advance_frame(&renderer->wall_animations[SOUTH]);
	advance_frame(&renderer->cat);
	advance_frame(&renderer->cat_walking);
	advance_frame(&renderer->cat_laying);
}
