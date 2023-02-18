/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 09:26:22 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/18 16:12:24 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static void	print_args(char **args);
static int	check_newline_flag(char **args, int *newline);

int	echo(t_cmd *cmd)
{
	print_args(cmd->args);
	return (0);
}

static void	print_args(char **args)
{
	int	i;
	int	newline;

	i = check_newline_flag(args, &newline);
	while (args[i] != NULL)
	{
		ft_printf("%s", args[i]);
		if (args[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (newline == TRUE)
		ft_printf("\n");
}

// Return the start index
static int	check_newline_flag(char **args, int *newline)
{
	int	start;

	start = 1;
	*newline = TRUE;
	while (args[start] != NULL && ft_strncmp(args[start], "-n", 3) == 0)
	{
		*newline = FALSE;
		start++;
	}
	return (start);
}
