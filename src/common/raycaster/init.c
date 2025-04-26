/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 00:43:43 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/21 04:15:40 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycaster.h"
#include "libft.h"
#include <math.h>

// TODO: are these angles correct?
// TODO: decide on projection plane or trig
t_ray	init_ray(t_raycaster *raycaster, int ray_count,
			t_dimensions *tile, t_player *player)
{
	t_ray	ray;

	ft_memset(&ray, 0, sizeof(ray));
	ray.id = ray_count;
	ray.world_pos = player->world_pos;
	ray.tile_index.x = player->world_pos.x / tile->width;
	ray.tile_index.y = player->world_pos.y / tile->height;
	ray.tile_offset.x = player->world_pos.x / tile->width;
	ray.tile_offset.y = player->world_pos.y / tile->height;
	ray.angle = raycaster->leftmost_ray_angle
		- (ray.id * raycaster->angle_increment);
	ray.dir.x = cos(ray.angle);
	ray.dir.y = -sin(ray.angle);
	return (ray);
}

/* Initialize the raycaster for the first time 
 * Set the number of rays to cast based on the screen width,
 * calculate the angle difference between each ray by using the field of view,
 * find the angle of where the first ray starts and the last ray ends,
 * assign an id to each ray so it knows which X of the screen slice it is */
t_raycaster	init_raycaster(t_player *player,
					t_dimensions *screen, t_dimensions *tile)
{
	t_raycaster	raycaster;
	int			ray_count;

	raycaster.ray_count = screen->width;
	raycaster.angle_increment = player->field_of_view / raycaster.ray_count;
	raycaster.leftmost_ray_angle = player->angle
		+ (player->field_of_view / 2);
	ray_count = 0;
	while (ray_count < raycaster.ray_count)
	{
		raycaster.rays[ray_count]
			= init_ray(&raycaster, ray_count, tile, player);
		ray_count++;
	}
	return (raycaster);
}
