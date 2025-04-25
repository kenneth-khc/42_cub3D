/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 22:38:09 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/26 05:19:17 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Raycaster.h"
#include "Vector.h"
#include <math.h>
#include <stdbool.h>

static void	update_raycaster(t_raycaster *raycaster, t_player *player,
				t_dimensions *tile);
static void	cast(t_ray *ray, t_player *player, t_map *map, t_doors *doors);
static void	check_ray_hit(t_ray *ray, t_map *map, t_doors *doors);

void	raycast(t_raycaster *raycaster, t_player *player, t_game *game)
{
	t_ray	*ray;
	int		x;

	update_raycaster(raycaster, &game->player, &game->tile);
	x = 0;
	while (x < game->screen.width)
	{
		ray = &raycaster->rays[x];
		cast(ray, player, &game->map, &game->doors);
		x++;
	}
}

/* Update the raycaster's angles and positions based on the new player
 * angles and positions */
static void	update_raycaster(t_raycaster *raycaster, t_player *player,
			t_dimensions *tile)
{
	int		i;
	t_ray	*ray;

	raycaster->leftmost_ray_angle = player->angle
		+ (player->field_of_view / 2);
	raycaster->rightmost_ray_angle = player->angle
		- (player->field_of_view / 2);
	i = 0;
	while (i < raycaster->ray_count)
	{
		ray = &raycaster->rays[i];
		ray->world_pos = player->world_pos;
		ray->tile_index.x = ray->world_pos.x / tile->width;
		ray->tile_index.y = ray->world_pos.y / tile->height;
		ray->tile_offset.x = ray->world_pos.x / tile->width;
		ray->tile_offset.y = ray->world_pos.y / tile->height;
		ray->angle = raycaster->leftmost_ray_angle
			- (ray->id * raycaster->angle_increment);
		ray->dir.x = cos(ray->angle);
		ray->dir.y = -sin(ray->angle);
		i++;
	}
}

/* Send forth a ray until it hits a wall. Behold, wizardry. */
static void	cast(t_ray *ray, t_player *player, t_map *map, t_doors *doors)
{
	init_dda(ray);
	ray->hit_door = false;
	while (!ray->hit)
	{
		if (ray->x_axis_distance < ray->y_axis_distance)
		{
			ray->tile_index.x += ray->x_step;
			ray->hit_side = HIT_VERTICAL;
			ray->x_axis_distance += ray->dx;
		}
		else
		{
			ray->tile_index.y += ray->y_step;
			ray->hit_side = HIT_HORIZONTAL;
			ray->y_axis_distance += ray->dy;
		}
		check_ray_hit(ray, map, doors);
	}
	get_distance(ray, player);
}

static void	check_ray_hit(t_ray *ray, t_map *map, t_doors *doors)
{
	t_door	*door;

	door = get_door(doors, ray->tile_index.x, ray->tile_index.y);
	if (is_wall(map, ray->tile_index.x, ray->tile_index.y))
	{
		ray->hit = true;
		check_wall_side_hit(ray);
	}
	else if (door && door->is_closed)
	{
		ray->hit_door = true;
		ray->hit = true;
		check_wall_side_hit(ray);
	}
}
