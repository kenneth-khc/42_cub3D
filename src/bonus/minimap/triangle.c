/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:52:28 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/24 19:23:32 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Triangle.h"
#include "Minimap.h"
#include "Player.h"
#include "Utils.h"
#include "Settings.h"
#include <math.h>

static double
cross_product(t_vec2i *edge_start, t_vec2i *edge_end, t_vec2i *point);

void	draw_player_indicator(t_minimap *minimap, t_camera *camera,
								t_player *player)
{
	t_bounding_box	box;
	t_triangle		triangle;
	t_vec2i			indicator_centre;
	double			left_angle;
	double			right_angle;

	box.start.x = camera->centre.x - minimap->player_box_half_dimension;
	box.start.y = camera->centre.y - minimap->player_box_half_dimension;
	box.end.x = camera->centre.x + minimap->player_box_half_dimension;
	box.end.y = camera->centre.y + minimap->player_box_half_dimension;
	indicator_centre.x = camera->centre.x
		- player->direction.x * PLAYER_INDICATOR_MAGNITUDE / 2;
	indicator_centre.y = camera->centre.y
		- player->direction.y * PLAYER_INDICATOR_MAGNITUDE / 2;
	triangle.a.x = indicator_centre.x
		+ player->direction.x * PLAYER_INDICATOR_MAGNITUDE;
	triangle.a.y = indicator_centre.y
		+ player->direction.y * PLAYER_INDICATOR_MAGNITUDE;
	left_angle = player->angle + radians(90);
	triangle.b.x = indicator_centre.x + cos(left_angle) * 10;
	triangle.b.y = indicator_centre.y + -sin(left_angle) * 10;
	right_angle = player->angle - radians(90);
	triangle.c.x = indicator_centre.x + cos(right_angle) * 10;
	triangle.c.y = indicator_centre.y + -sin(right_angle) * 10;
	draw_triangle(&box, &triangle, &minimap->img);
}

void	draw_triangle(t_bounding_box *box, t_triangle *triangle, t_image *img)
{
	t_vec2i			draw_pos;
	const t_colour	pink = create_colour(0x0, 247, 171, 209);

	draw_pos.y = box->start.y;
	while (draw_pos.y < box->end.y)
	{
		draw_pos.x = box->start.x;
		while (draw_pos.x < box->end.x)
		{
			if (in_triangle(draw_pos, triangle))
			{
				draw_pixel(img, draw_pos.x, draw_pos.y, pink);
			}
			draw_pos.x++;
		}
		draw_pos.y++;
	}
}

bool	in_triangle(t_vec2i point, t_triangle *triangle)
{
	const double	cross_ab_ap
		= cross_product(&triangle->a, &triangle->b, &point);
\
	const double	cross_bc_bp
		= cross_product(&triangle->b, &triangle->c, &point);
\
	const double	cross_ca_cp
		= cross_product(&triangle->c, &triangle->a, &point);

	return ((cross_ab_ap < 0 && cross_bc_bp < 0 && cross_ca_cp < 0)
		|| (cross_ab_ap > 0 && cross_bc_bp > 0 && cross_ca_cp > 0));
}

static
double	cross_product(t_vec2i *edge_start, t_vec2i *edge_end, t_vec2i *point)
{
	t_vec2i	start_to_end;
	t_vec2i	start_to_point;

	start_to_end.x = edge_end->x - edge_start->x;
	start_to_end.y = edge_end->y - edge_start->y;
	start_to_point.x = point->x - edge_start->x;
	start_to_point.y = point->y - edge_start->y;
	return (start_to_end.x * start_to_point.y
		- start_to_end.y * start_to_point.x);
}
