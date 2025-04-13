/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 01:00:16 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/14 01:01:10 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Minimap.h"
#include "Map.h"

void	init_minimap(t_game *game, t_map *map, t_minimap *minimap)
{
	(void)map;
	minimap->display = true;
	minimap->width = game->screen.width * MINIMAP_SCALE;
	minimap->height = game->screen.height * MINIMAP_SCALE;
	create_image(game->mlx, &minimap->img, minimap->width, minimap->height);
	minimap->img.pos.x = 10;
	minimap->img.pos.y = 10;
	update_minimap(minimap, game);
}
