/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 04:18:27 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/26 04:24:24 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Doors.h"
#include "Keys.h"
#include "Game.h"

static t_door
*touch_door(const t_player *player, t_doors *doors, t_game *game);

int	open_door(t_game *game)
{
	const t_key		*spacebar_key = &game->keystates.keys[KEY_SPACEBAR];
	t_player *const	player = &game->player;
	t_door			*door_touched;

	if (!pressed_and_released(spacebar_key, KEY_SPACEBAR))
	{
		return (0);
	}
	door_touched = touch_door(&game->player, &game->doors, game);
	if (!door_touched)
	{
		return (1);
	}
	if (door_touched->tile_pos.x == player->tile_index.x
		&& door_touched->tile_pos.y == player->tile_index.y)
	{
		return (1);
	}
	door_touched->is_closed = !door_touched->is_closed;
	return (1);
}

static
t_door	*touch_door(const t_player *player, t_doors *doors, t_game *game)
{
	t_vec2i			tile;
	const double	dx = player->direction.x * PLAYER_TOUCH_MAGNITUDE;
	const double	dy = player->direction.y * PLAYER_TOUCH_MAGNITUDE;

	tile.x = (player->world_pos.x + dx) / game->tile.width;
	tile.y = (player->world_pos.y + dy) / game->tile.height;
	return (get_door(doors, tile.x, tile.y));
}
