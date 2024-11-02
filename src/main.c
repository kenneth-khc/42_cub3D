/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 08:42:45 by kecheong          #+#    #+#             */
/*   Updated: 2024/11/01 15:34:27 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdbool.h>
#include "Game.h"
#include "Keys.h"
#include "Map.h"
#include "Renderer.h"
#include "Raycaster.h"

int	game_loop(t_game *game)
{
	mlx_clear_window(game->mlx, game->window);
	raycast(&game->raycaster, game, &game->player);
	render(game, &game->raycaster);
	return (0);
}

int	main(void)
{
	t_game	game;

	game.mlx = mlx_init();
	game.screen_width = 500;
	game.screen_height = 500;
	game.window = mlx_new_window(game.mlx, game.screen_width,
			game.screen_height, "cute3D");
	game.tile_width = 64.0;
	game.tile_height = 64.0;
	init_player(&game.player);
	init_map(&game.map, &game);
	init_background(&game);
	mlx_hook(game.window, KEYPRESS_EVENT, 1L << 0, process_key, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
}
