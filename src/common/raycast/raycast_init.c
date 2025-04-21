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
void	init_ray(t_ray *ray, t_raycaster *raycaster, int ray_count,
			t_dimensions *tile, t_player *player)
{
	const double	camera_x = 2 * ray_count / (double)raycaster->ray_count - 1;

	ft_memset(ray, 0, sizeof(*ray));
	ray->id = ray_count;
	ray->world_pos = player->world_pos;
	ray->tile_index.x = player->world_pos.x / tile->width;
	ray->tile_index.y = player->world_pos.y / tile->height;
	ray->tile_offset.x = player->world_pos.x / tile->width;
	ray->tile_offset.y = player->world_pos.y / tile->height;
	ray->angle = raycaster->leftmost_ray_angle
		- (ray->id * raycaster->angle_increment);
	ray->dir.x = player->direction.x
		+ raycaster->projection_plane.x * camera_x;
	ray->dir.y = player->direction.y
		+ raycaster->projection_plane.y * camera_x;
	ray->dir.x = cos(ray->angle);
	ray->dir.y = -sin(ray->angle);
}

/* Initialize the raycaster for the first time 
 * Set the number of rays to cast based on the screen width,
 * calculate the angle difference between each ray by using the field of view,
 * find the angle of where the first ray starts and the last ray ends,
 * assign an id to each ray so it knows which X of the screen slice it is */
void	init_raycaster(t_raycaster *raycaster, t_player *player,
					t_dimensions *screen, t_dimensions *tile)
{
	t_ray	*ray;
	int		ray_count;

	raycaster->ray_count = screen->width;
	raycaster->angle_increment = player->field_of_view / raycaster->ray_count;
	raycaster->leftmost_ray_angle = player->angle
		+ (player->field_of_view / 2);
	raycaster->projection_plane.x = 0;
	raycaster->projection_plane.y = 1;
	ray_count = 0;
	while (ray_count < raycaster->ray_count)
	{
		ray = &raycaster->rays[ray_count];
		init_ray(ray, raycaster, ray_count, tile, player);
		ray_count++;
	}
}
