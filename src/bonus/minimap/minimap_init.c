/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 01:00:16 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/18 04:58:30 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Minimap.h"
#include "Map.h"

void	init_minimap(t_game *game, t_map *map, t_minimap *minimap)
{
	int	width = game->screen.width * MINIMAP_SCALE;
	int	height = game->screen.height * MINIMAP_SCALE;
	create_image(game->mlx, &minimap->img, width, height);
	minimap->img.pos.x = MINIMAP_X_OFFSET;
	minimap->img.pos.y = MINIMAP_Y_OFFSET;
	(void)map;
	minimap->display = true;
	printf("%d %d\n", minimap->img.width, minimap->img.height);
	update_minimap(minimap, game);
}
