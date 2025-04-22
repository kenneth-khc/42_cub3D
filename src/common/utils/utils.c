/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 04:15:56 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/23 22:46:53 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include <stdlib.h>

void	error(const char *err_msg)
{
	ft_dprintf(STDERR_FILENO, "Error\n");
	ft_dprintf(STDERR_FILENO, err_msg);
	exit(1);
}

int	count_occurences(char c, const char *string)
{
	size_t	occurences;

	occurences = 0;
	while (*string)
	{
		if (*string == c)
		{
			occurences++;
		}
		string++;
	}
	return (occurences);
}

void	free_2d_array(char **arr)
{
	void	*ptr;

	ptr = arr;
	while (*arr)
	{
		free(*arr);
		arr++;
	}
	free(ptr);
}
