/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 22:47:40 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/23 00:06:44 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include <mlx.h>
#include <stdlib.h>

int	close_game(t_game *game)
{
	destroy_map(&game->map);
	destroy_image(game->mlx, &game->world_3d);
	destroy_image(game->mlx, &game->renderer.wall_textures[0]);
	destroy_image(game->mlx, &game->renderer.wall_textures[1]);
	destroy_image(game->mlx, &game->renderer.wall_textures[2]);
	destroy_image(game->mlx, &game->renderer.wall_textures[3]);
	mlx_destroy_window(game->mlx, game->window);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
}
