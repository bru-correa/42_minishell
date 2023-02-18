/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 01:26:24 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/18 01:38:19 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(void)
{
	char	*buffer;
	char	*path;

	buffer = NULL;
	path = getcwd(buffer, 0);
	if (path)
	{
		ft_printf("%s\n", path);
		free(path);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
