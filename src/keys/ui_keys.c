/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 22:47:40 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/13 23:16:10 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include <mlx.h>
#include <stdlib.h>

void	toggle_minimap(void *ptr)
{
	t_game *const		game = (t_game *)ptr;
	const t_key			*m_key = &game->keystates.keys[KEY_M];
	static t_key_state	prev_m_key_state = NONE;

	if (prev_m_key_state & PRESS && m_key->state & RELEASE)
	{
		game->minimap.display = !game->minimap.display;
	}
	prev_m_key_state = m_key->state;
}

void	close_game(void *ptr)
{
	t_game *const	game = (t_game*)ptr;

	mlx_destroy_image(game->mlx, game->minimap.img.instance);
	mlx_destroy_image(game->mlx, game->world_3d.instance);
	mlx_destroy_image(game->mlx, game->renderer.textures[0].instance);
	mlx_destroy_image(game->mlx, game->renderer.textures[1].instance);
	mlx_destroy_image(game->mlx, game->renderer.textures[2].instance);
	mlx_destroy_image(game->mlx, game->renderer.textures[3].instance);
	mlx_destroy_window(game->mlx, game->window);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
}
