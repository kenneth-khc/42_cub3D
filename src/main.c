/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 08:42:45 by kecheong          #+#    #+#             */
/*   Updated: 2024/10/30 15:11:10 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "Game.h"
#include "Keys.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	process_key(int keycode)
{
	if (keycode == KEY_ESC)
	{
		exit(0);
	}
	return (0);
}

int	game_loop(t_Game *game)
{
	mlx_clear_window(game->mlx, game->window);
	mlx_put_image_to_window(game->mlx, game->window, game->map.img.instance, 0, 0);
	return (0);
}

int	main(void)
{
	t_Game	game;

	game.mlx = mlx_init();
	game.screen_width = 1280;
	game.screen_height = 720;
	game.window = mlx_new_window(game.mlx, game.screen_width,
			game.screen_height, "Hello World");
	init_player(&game.player);
	init_map(&game.map, game.mlx);
	mlx_key_hook(game.window, process_key, NULL);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
}
