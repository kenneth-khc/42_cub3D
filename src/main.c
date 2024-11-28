/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 08:42:45 by kecheong          #+#    #+#             */
/*   Updated: 2024/11/17 01:54:59 by kecheong         ###   ########.fr       */
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

int	main(void)
{
	t_game		game;

	game = (t_game){0}; // maybe not necessary if we initialize everything properly before reading
	set_colour_table(&game.colours); // probably remove later
	init_game(&game);
	init_player(&game.player);
	init_map(&game.map, &game);
	init_raycaster(&game.raycaster, &game.player, &game);
	init_minimap(&game, &game.map, &game.minimap);
	init_world_3d(&game);
	mlx_hook(game.window, KEYPRESS_EVENT, KEYPRESS_MASK, process_key, &game);
	mlx_hook(game.window, MOUSEMOVE_EVENT, POINTER_MOTION_MASK, process_mouse, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->screen_width = SCREEN_WIDTH;
	game->screen_height = SCREEN_HEIGHT;
	game->window = mlx_new_window(game->mlx, game->screen_width,
			game->screen_height, "cute3D");
	game->tile_width = 50;
	game->tile_height = 50;
}

int	game_loop(t_game *game)
{
	mlx_clear_window(game->mlx, game->window);
	raycast(&game->raycaster, &game->player, game);
	render(game, &game->raycaster);
	return (0);
}

