/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:19:41 by kecheong          #+#    #+#             */
/*   Updated: 2024/11/01 15:34:29 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "Vector.h"

t_vec2d	copy_vector_double(t_vec2d *src)
{
	t_vec2d	dst;

	dst.x = src->x;
	dst.y = src->y;
	return (dst);
}

t_vec2i	copy_vector_int(t_vec2i *src)
{
	t_vec2i	dst;

	dst.x = src->x;
	dst.y = src->y;
	return (dst);
}

t_vec2i	v2d_to_v2i(t_vec2d d)
{
	t_vec2i	i;

	i.x = d.x;
	i.y = d.y;
	return (i);
}

bool	compare_vectors(t_vec2i *v1, t_vec2i *v2)
{
	return (v1->x == v2->x && v1->y == v2->y);
}
