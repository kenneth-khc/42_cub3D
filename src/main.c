/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 08:42:45 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/14 06:10:28 by kecheong         ###   ########.fr       */
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

#include <fcntl.h> // del
#include <unistd.h>
#include <limits.h>

int	main(void)
{
	t_game	game;

	// maybe not necessary if we initialize everything properly before reading
	game = (t_game){0};
	set_colour_table(&game.colours); // probably remove later
	init_game(&game);
	init_keybindings(&game.keystates);
	init_player(&game.player);
	init_map(&game.map, &game, &game.player);
	init_raycaster(&game.raycaster, &game.player, &game);
	init_minimap(&game, &game.map, &game.minimap);
	create_image(game.mlx, &game.world_3d, game.screen.width,
		game.screen.height);
	init_renderer(&game.renderer, &game, &game.world_3d, game.screen);
	mlx_hook(game.window,
		KEYPRESS_EVENT, KEYPRESS_MASK, press_key, &game.keystates);
	mlx_hook(game.window,
		KEYRELEASE_EVENT, KEYRELEASE_EVENT, release_key, &game.keystates);
	mlx_hook(game.window,
		MOUSEMOVE_EVENT, POINTER_MOTION_MASK, process_mouse, &game);
	mlx_mouse_hide(game.mlx, game.window);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->screen.width = SCREEN_WIDTH;
	game->screen.height = SCREEN_HEIGHT;
	game->window = mlx_new_window(game->mlx, game->screen.width,
			game->screen.height, WINDOW_TITLE);
	game->tile_width = TILE_WIDTH;
	game->tile_height = TILE_HEIGHT;
}

int	game_loop(t_game *game)
{
	process_keys(&game->keystates, game);
	mlx_clear_window(game->mlx, game->window);
	raycast(&game->raycaster, &game->player, game);
	render(game, &game->renderer, &game->raycaster);
	return (0);
}
