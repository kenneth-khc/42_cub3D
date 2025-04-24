/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Triangle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:12:22 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/24 22:36:49 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_H
# define TRIANGLE_H

# include "Vector.h"
# include "Image.h"

typedef struct s_triangle
{
	t_vec2i	a;
	t_vec2i	b;
	t_vec2i	c;
}	t_triangle;

typedef struct s_bounding_box
{
	t_vec2i	start;
	t_vec2i	end;
}	t_bounding_box;

void	draw_triangle(t_bounding_box *box, t_triangle *triangle, t_image *img);
bool	in_triangle(t_vec2i point, t_triangle *triangle);

#endif
