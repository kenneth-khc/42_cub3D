/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 08:42:45 by kecheong          #+#    #+#             */
/*   Updated: 2024/10/30 22:37:10 by kecheong         ###   ########.fr       */
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
	render(game);
	return (0);
}

int	main(void)
{
	t_game	game;

	game.mlx = mlx_init();
	game.screen_width = 1280;
	game.screen_height = 720;
	game.window = mlx_new_window(game.mlx, game.screen_width,
			game.screen_height, "cute3D");
	init_player(&game.player);
	init_map(&game.map, &game);
	init_background(&game.floor, &game.ceiling, &game);
	mlx_hook(game.window, KEYPRESS_EVENT, 0, process_key, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
}
