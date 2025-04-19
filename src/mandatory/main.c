/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 08:42:45 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/19 22:21:16 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdbool.h>
#include "Game.h"
#include "Keys.h"
#include "Map.h"
#include "Renderer.h"
#include "Raycaster.h"
#include "Colours.h" // probably don't need all these colours, remove later
#include "Parse.h"

#include <fcntl.h> // del
#include <unistd.h>
#include <limits.h>
#include "ft_dprintf.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_config	config;
	t_game		game;

	// maybe not necessary if we initialize everything properly before reading
	game = (t_game){0};
	set_colour_table(&game.colours); // probably remove later
	if (argc != 2)
	{
		error("Usage: ./cub3D <.cub file>\n");
	}
	config = parse(*++argv);
	validate_map(&config.map);
	init_game(&game, &config);
	mlx_loop(game.mlx);
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
	mlx_hook(game->window,
		KEYPRESS_EVENT, KEYPRESS_MASK, press_key, &game->keystates);
	mlx_hook(game->window,
		KEYRELEASE_EVENT, KEYRELEASE_EVENT, release_key, &game->keystates);
	mlx_hook(game->window,
		MOUSEMOVE_EVENT, POINTER_MOTION_MASK, process_mouse, game);
	mlx_mouse_hide(game->mlx, game->window);
	mlx_loop_hook(game->mlx, game_loop, game);
}

void	update(t_game *game, t_player *player)
{
	if (player->is_moving)
	{
		/*printf("%f %f", player->world_pos.x, player->world_pos.y);*/
		/*printf(" => ");*/
		player->world_pos.x += player->delta.x;
		player->world_pos.y += player->delta.y;
		/*printf("%f %f\n", player->world_pos.x, player->world_pos.y);*/
		player->tile_index.x = player->world_pos.x / game->tile.width;
		player->tile_index.y = player->world_pos.y / game->tile.height;
		// TODO: fix this
		/*update_map(&game->map, player);*/
		player->is_moving = false;
		player->delta.x = 0;
		player->delta.y = 0;
	}
	/*update_minimap(&game->minimap, game);*/
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

void	error(const char *err_msg)
{
	ft_dprintf(STDERR_FILENO, "Error\n");
	ft_dprintf(STDERR_FILENO, err_msg);
	exit(1);
}
