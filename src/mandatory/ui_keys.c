/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 22:47:40 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/22 04:17:39 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include <mlx.h>
#include <stdlib.h>

int	close_game(void *ptr)
{
	t_game *const	game = (t_game*)ptr;

	mlx_destroy_image(game->mlx, game->world_3d.instance);
	mlx_destroy_image(game->mlx, game->renderer.wall_textures[0].instance);
	mlx_destroy_image(game->mlx, game->renderer.wall_textures[1].instance);
	mlx_destroy_image(game->mlx, game->renderer.wall_textures[2].instance);
	mlx_destroy_image(game->mlx, game->renderer.wall_textures[3].instance);
	mlx_destroy_window(game->mlx, game->window);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
}
