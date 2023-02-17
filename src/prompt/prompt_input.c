/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:42:06 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/17 11:32:56 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_user(t_env_var **env_list);
static char	*get_pwd(void);
static char	*get_prompt(t_env_var **env_list);

char	*prompt_input(t_env_var **env_list)
{
	char	*input;
	char	*prompt;

	prompt = get_prompt(env_list);
	input = readline(prompt);
	free(prompt);
	if (input == NULL)
	{
		input = ft_strdup("exit");
		ft_printf("exit\n");
		return (input);
	}
	add_history(input);
	return (input);
}

static char	*get_user(t_env_var **env_list)
{
	char	*user;

	user = search_env_var(env_list, "USER");
	if (ft_strncmp(user, "", 1) == 0)
	{
		free(user);
		user = ft_strdup("UNKNOWN");
	}
	return (user);
}

static char	*get_pwd(void)
{
	char	*pwd;
	char	*buffer;

	buffer = NULL;
	pwd = getcwd(buffer, 0);
	return (pwd);
}

static char	*get_prompt(t_env_var **env_list)
{
	char	*user;
	char	*pwd;
	char	*prompt;

	user = get_user(env_list);
	pwd = get_pwd();
	prompt = get_prompt_str(user, pwd);
	free(user);
	free(pwd);
	return (prompt);
}
