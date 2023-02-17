/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 11:16:21 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/17 14:08:47 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_user_prompt(char *user);
static char	*join_pwd_prompt(char *prompt, char *pwd);
static char	*join_shell_prompt(char *prompt);
static char	*join_arrow_prompt(char *prompt);

char	*get_prompt_str(char *user, char *pwd)
{
	char	*prompt;

	prompt = get_user_prompt(user);
	prompt = join_shell_prompt(prompt);
	prompt = join_pwd_prompt(prompt, pwd);
	prompt = join_arrow_prompt(prompt);
	return (prompt);
}

static char	*get_user_prompt(char *user)
{
	char	*prompt;

	prompt = ft_strjoin(RL_COLOR_GREEN, user);
	return (prompt);
}

static char	*join_shell_prompt(char *prompt)
{
	char	*temp;

	temp = prompt;
	prompt = ft_strjoin(prompt, RL_COLOR_RED);
	free(temp);
	temp = prompt;
	prompt = ft_strjoin(prompt, "@mini$HELL:");
	free(temp);
	return (prompt);
}

static char	*join_pwd_prompt(char *prompt, char *pwd)
{
	char	*temp;

	temp = prompt;
	prompt = ft_strjoin(prompt, RL_COLOR_YELLOW);
	free(temp);
	temp = prompt;
	prompt = ft_strjoin(prompt, pwd);
	free(temp);
	return (prompt);
}

static char	*join_arrow_prompt(char *prompt)
{
	char	*temp;

	temp = prompt;
	if (g_exit_status == 0)
		prompt = ft_strjoin(prompt, RL_COLOR_GREEN);
	else
		prompt = ft_strjoin(prompt, RL_COLOR_RED);
	free(temp);
	temp = prompt;
	prompt = ft_strjoin(prompt, " -> ");
	free(temp);
	temp = prompt;
	prompt = ft_strjoin(prompt, RL_COLOR_RESET);
	free(temp);
	return (prompt);
}
