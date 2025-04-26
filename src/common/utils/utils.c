/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 04:15:56 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/24 02:57:44 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include <stdlib.h>

/* Log to stderr and exit */
/*void	error(const char *err_msg)*/
/*{*/
/*	ft_dprintf(STDERR_FILENO, "Error\n");*/
/*	ft_dprintf(STDERR_FILENO, err_msg);*/
/*	exit(1);*/
/*}*/

void	error(char *err_msg, const char *thing)
{
	if (thing)
	{
		ft_dprintf(STDERR_FILENO, "Error\n%s `%s`\n", err_msg, thing);
	}
	else
	{
		ft_dprintf(STDERR_FILENO, "Error\n%s\n", err_msg);
	}
	exit(1);
}

/* malloc() wrapper. succeed or die. */
void	*xmalloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		error("out of memory", NULL);
	}
	return (ptr);
}

/* Counts the number of occurrences of a character in a given string */
int	count_occurrences(char c, const char *string)
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

/* Frees the strings in a NULL terminated char* array and then free the array
 * itself */
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
