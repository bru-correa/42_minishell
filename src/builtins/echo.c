/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 09:26:22 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/01/27 10:09:59 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static void	print_args(char **args);

void	echo(t_cmd *cmd)
{
	print_args(cmd->args);
	g_exit_status = 0;
}

static void	print_args(char **args)
{
	int	i;
	int	newline;

	newline = TRUE;
	i = 1;
	while (args[i] != NULL)
	{
		if (ft_strncmp(args[i], "-n", 3) == 0)
			newline = FALSE;
		ft_printf("%s", args[i]);
		if (args[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (newline == TRUE)
		ft_printf("\n");
}
