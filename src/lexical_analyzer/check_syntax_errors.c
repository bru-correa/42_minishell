/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:27:59 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/11/23 19:44:32 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_syntax_error(char *invalid_token);
static int	check_redirection(t_slist *token, char *operator);
static int	check_pipe(t_slist *token);
static int	check_next_token(t_slist *token);

int	check_syntax_errors(t_slist **tokens)
{
	t_slist	*current_token;

	current_token = *tokens;
	while (current_token != NULL)
	{
		if (check_redirection(current_token, ">") == FAILURE)
			return (FAILURE);
		else if (check_redirection(current_token, "<") == FAILURE)
			return (FAILURE);
		else if (check_pipe(current_token) == FAILURE)
			return (FAILURE);
		current_token = current_token->next;
	}
	return (SUCCESS);
}

static int	check_redirection(t_slist *token, char *operator)
{
	if (ft_strncmp(token->data, operator, 1) == 0)
	{
		if (token->next == NULL)
		{
			print_syntax_error("newline");
			return (FAILURE);
		}
		else if (check_next_token(token) == FAILURE)
		{
			print_syntax_error(token->next->data);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

// The pipe can be last character of a cmdline
static int	check_pipe(t_slist *token)
{
	if (ft_strncmp(token->data, "|", 1) == 0)
	{
		if (token->next == NULL)
			return (SUCCESS);
		else if (check_next_token(token) == FAILURE)
		{
			print_syntax_error(token->next->data);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

static int	check_next_token(t_slist *token)
{
	if (ft_strncmp(token->next->data, ">", 1) == 0)
		return (FAILURE);
	else if (ft_strncmp(token->next->data, "<", 1) == 0)
		return (FAILURE);
	else if (ft_strncmp(token->next->data, "|", 1) == 0)
		return (FAILURE);
	return (SUCCESS);
}

static void	print_syntax_error(char *invalid_token)
{
	ft_putstr_fd("minish: ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(invalid_token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}