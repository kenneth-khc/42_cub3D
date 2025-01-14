/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:06:54 by kytan             #+#    #+#             */
/*   Updated: 2025/01/14 15:24:06 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

typedef enum    e_error
{
    E_TOO_MANY_ARGS,
    E_INVALID_FILE,
    E_INVALID_MAP_ELEMENTS,
    E_CUB_FILETYPE,
    E_FILE_NOT_FOUND,
    E_FILE_DENIED_PERM,
    E_FILE_NO_ACCESS
}   t_error;