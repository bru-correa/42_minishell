/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goodbye.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 05:30:09 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/17 06:15:31 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_div(void);

void	goodbye(t_env_var **env_list)
{
	char	*user;

	user = search_env_var(env_list, "USER");
	if (ft_strncmp(user, "", 1) == 0)
	{
		free(user);
		user = ft_strdup("UNKNOWN");
	}
	ft_printf(COLOR_RED);
	print_div();
	ft_printf(COLOR_GREEN);
	ft_printf("   %s escaped from $HELL... for now\n", user);
	ft_printf(COLOR_RED);
	print_div();
	ft_printf(COLOR_RESET);
	free(user);
}

static void	print_div(void)
{
	ft_printf("=======================================================\n");
}
