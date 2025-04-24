/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:29:47 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/24 17:20:14 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Settings.h"
#include "Minimap.h"
#include "Renderer.h"
#include "Utils.h"
#include <mlx.h>

static void	set_game_dimensions(t_game *game);
static void	*init_mlx(void);
static void	*init_window(void *mlx, t_dimensions *screen);

void	init_game(t_game *game, t_config *config)
{
	set_game_dimensions(game);
	game->mlx = init_mlx();
	game->keystates = init_keybindings();
	game->map = init_map(config);
	game->player = init_player(&game->map);
	game->minimap = init_minimap(game);
	game->raycaster = init_raycaster(&game->player, &game->screen, &game->tile);
	game->world_3d = create_image(game->mlx, game->screen.width,
			game->screen.height);
	game->renderer = init_renderer(config, game, &game->world_3d, game->screen);
	game->window = init_window(game->mlx, &game->screen);
}

static void	*init_mlx(void)
{
	void *const	mlx = mlx_init();

	if (mlx == NULL)
	{
		error("mlx_init() failed\n");
	}
	return (mlx);
}

static void	*init_window(void *mlx, t_dimensions *screen)
{
	void *const	window = mlx_new_window(mlx,
			screen->width, screen->height, WINDOW_TITLE);

	if (window == NULL)
	{
		error("mlx_new_window() failed\n");
	}
	return (window);
}

static void	set_game_dimensions(t_game *game)
{
	game->screen.width = SCREEN_WIDTH;
	game->screen.height = SCREEN_HEIGHT;
	game->tile.width = TILE_WIDTH;
	game->tile.height = TILE_HEIGHT;
}
