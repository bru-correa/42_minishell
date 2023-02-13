/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramondo <jramondo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:37:48 by jramondo          #+#    #+#             */
/*   Updated: 2023/02/13 05:15:15 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    clear_fds(void)
{
    int fd;

    fd = open("/tmp/tmpfile", O_RDONLY | O_CREAT);
    if (fd < 0)
        return ;
    while (fd > STDERR_FILENO)
        close(fd--);
    unlink("/tmp/tmpfile");
}
