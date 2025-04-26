/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 08:42:45 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/23 00:06:57 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdbool.h>
#include "Game.h"
#include "Parse.h"
#include "Keys.h"
#include "Renderer.h"
#include "Raycaster.h"
#include "Utils.h"
#include <unistd.h>
#include <limits.h>

static void
setup_event_hooks(t_game *game, void *window, t_keystates *keystates);

int	main(int argc, char **argv)
{
	t_config	config;
	t_game		game;

	game = (t_game){0};
	if (argc != 2)
	{
		error("Usage: ./cub3D <.cub file>\n", NULL);
	}
	config = parse(*++argv);
	validate_map(&config.map);
	init_game(&game, &config);
	setup_event_hooks(&game, game.window, &game.keystates);
	destroy_config(&config);
	print_map(&game.map);
	mlx_loop(game.mlx);
}

static
void	setup_event_hooks(t_game *game, void *window, t_keystates *keystates)
{
	mlx_hook(window, KEY_PRESS_EV, KEY_PRESS_MASK, press_key, keystates);
	mlx_hook(window, KEY_RELEASE_EV, KEY_RELEASE_MASK, release_key, keystates);
	mlx_hook(window, MOUSE_MOVE_EV, POINTER_MOTION_MASK, process_mouse, game);
	mlx_hook(window, DESTROY_WINDOW_EV, 0, close_game, game);
	mlx_mouse_hide(game->mlx, window);
	mlx_loop_hook(game->mlx, game_loop, game);
}

int	game_loop(t_game *game)
{
	process_keys(&game->keystates, game);
	update(game);
	raycast(&game->raycaster, &game->player, game);
	render(game, &game->renderer, &game->raycaster);
	return (0);
}
