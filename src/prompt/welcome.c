/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 05:06:13 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/17 06:16:19 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_div(void);

void	welcome(t_env_var **env_list)
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
	ft_printf(COLOR_YELLOW);
	ft_printf("   %s is entering The Domains of $HELL\n", user);
	ft_printf(COLOR_RED);
	print_div();
	ft_printf(COLOR_RESET);
	free(user);
}

static void	print_div(void)
{
	ft_printf("=======================================================\n");
}
