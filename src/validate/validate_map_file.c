/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:02:25 by kytan             #+#    #+#             */
/*   Updated: 2025/01/14 15:51:58 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "Error.h"

#define FILE_EXTENSION_LEN 4

int non_cub_file(char *file)
{
    return (ft_strlen(file) < 5 ||
    ft_strncmp(file + ft_strlen(file) - FILE_EXTENSION_LEN,
    ".cub", FILE_EXTENSION_LEN));
}

int validate_file(char *file)
{
    int     fd;

    if (non_cub_file(file))
        return (stderr_msg(E_CUB_FILETYPE, file));
    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        if (errno == ENOENT)
            return (stderr_msg(E_FILE_NOT_FOUND, file));
        else if (errno == EACCES)
            return (stderr_msg(E_FILE_DENIED_PERM, file));
        else
            return (stderr_msg(E_FILE_NO_ACCESS, file));
    }
    close(fd);
}