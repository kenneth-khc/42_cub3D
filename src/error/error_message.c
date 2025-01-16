/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:35:37 by kytan             #+#    #+#             */
/*   Updated: 2025/01/16 14:39:50 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../include/Error.h"

int stderr_msg(t_error error, char *args)
{
    E_TOO_MANY_ARGS,
    E_INVALID_FILE,
    E_INVALID_MAP_ELEMENTS,
    E_CUB_FILETYPE,
    E_FILE_NOT_FOUND,
    E_FILE_DENIED_PERM,
    E_FILE_NO_ACCESS
}