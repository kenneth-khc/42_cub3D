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

t_minimap	init_minimap(t_game *game)
{
	t_minimap	minimap;
	const int	width = game->screen.width * MINIMAP_SCALE;
	const int	height = game->screen.height * MINIMAP_SCALE;

	minimap.img = create_image(game->mlx, width, height);
	minimap.img.pos.x = MINIMAP_X_OFFSET;
	minimap.img.pos.y = MINIMAP_Y_OFFSET;
	minimap.display = true;
	update_minimap(&minimap, game);
	return (minimap);
}
