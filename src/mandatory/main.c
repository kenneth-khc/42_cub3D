/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 08:42:45 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/22 04:16:34 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdbool.h>
#include "Game.h"
#include "Keys.h"
#include "Map.h"
#include "Renderer.h"
#include "Raycaster.h"
#include "Parse.h"
#include "Utils.h"

#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_config	config;
	t_game		game;

	game = (t_game){0};
	if (argc != 2)
	{
		error("Usage: ./cub3D <.cub file>\n");
	}
	config = parse(*++argv);
	validate_map(&config.map);
	init_game(&game, &config);
	mlx_loop(game.mlx);
}

void	setup_event_hooks(t_game *game, void *window, t_keystates *keystates)
{
	mlx_hook(window, KEY_PRESS_EV, KEY_PRESS_MASK, press_key, keystates);
	mlx_hook(window, KEY_RELEASE_EV, KEY_RELEASE_MASK, release_key, keystates);
	mlx_hook(window, MOUSE_MOVE_EV, POINTER_MOTION_MASK, process_mouse, game);
	mlx_hook(window, DESTROY_WINDOW_EV, 0, close_game, game);
	mlx_mouse_hide(game->mlx, window);
	mlx_loop_hook(game->mlx, game_loop, game);
}

void	init_game(t_game *game, t_config *config)
{
	game->mlx = mlx_init();
	if (game->mlx == NULL)
	{
		error("mlx_init() failed\n");
	}
	game->screen.width = SCREEN_WIDTH;
	game->screen.height = SCREEN_HEIGHT;
	game->tile.width = TILE_WIDTH;
	game->tile.height = TILE_HEIGHT;
	init_keybindings(&game->keystates);
	init_map(&game->map, config);
	init_player(&game->player, &game->map);
	init_raycaster(&game->raycaster, &game->player, &game->screen, &game->tile);
	create_image(game->mlx, &game->world_3d, game->screen.width,
		game->screen.height);
	init_renderer(&game->renderer, config, game, &game->world_3d, game->screen);
	game->window = mlx_new_window(game->mlx, game->screen.width,
			game->screen.height, WINDOW_TITLE);
	if (game->window == NULL)
	{
		error("mlx_new_window() failed\n");
	}
	setup_event_hooks(game, game->window, &game->keystates);
}

void	update(t_game *game, t_player *player)
{
	if (player->is_moving)
	{
		player->world_pos.x += player->delta.x;
		player->world_pos.y += player->delta.y;
		player->tile_index.x = player->world_pos.x / game->tile.width;
		player->tile_index.y = player->world_pos.y / game->tile.height;
		player->is_moving = false;
		player->delta.x = 0;
		player->delta.y = 0;
	}
}

int	game_loop(t_game *game)
{
	mlx_clear_window(game->mlx, game->window);
	process_keys(&game->keystates, game);
	update(game, &game->player);
	raycast(&game->raycaster, &game->player, game);
	render(game, &game->renderer, &game->raycaster);
	return (0);
}
