/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 22:47:40 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/26 05:12:15 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include <mlx.h>
#include <stdlib.h>

int	toggle_minimap(t_game *game)
{
	const t_key	*m_key = &game->keystates.keys[KEY_M];

	if (pressed_and_released(m_key, KEY_M))
	{
		game->minimap.display = !game->minimap.display;
	}
	return (1);
}

int	close_game(t_game *game)
{
	t_renderer *const	renderer = &game->renderer;

	destroy_map(&game->map);
	destroy_image(game->mlx, &game->minimap.img);
	destroy_image(game->mlx, &game->world_3d);
	free(game->doors.ptr);
	destroy_animation(game->mlx, &renderer->wall_animations[0]);
	destroy_animation(game->mlx, &renderer->wall_animations[1]);
	destroy_animation(game->mlx, &renderer->wall_animations[2]);
	destroy_animation(game->mlx, &renderer->wall_animations[3]);
	destroy_animation(game->mlx, &renderer->cat);
	destroy_animation(game->mlx, &renderer->cat_walking);
	destroy_animation(game->mlx, &renderer->cat_laying);
	destroy_animation(game->mlx, &renderer->door_animation);
	mlx_destroy_window(game->mlx, game->window);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
}
