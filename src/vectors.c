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

t_vector_double	copy_vector_double(t_vector_double *src)
{
	t_vector_double	dst;

	dst.x = src->x;
	dst.y = src->y;
	return (dst);
}

t_vector_int	copy_vector_int(t_vector_int *src)
{
	t_vector_int	dst;

	dst.x = src->x;
	dst.y = src->y;
	return (dst);
}

bool	compare_vectors(t_vector_int *v1, t_vector_int *v2)
{
	return (v1->x == v2->x && v1->y == v2->y);
}
