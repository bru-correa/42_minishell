/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:27:59 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/10/28 20:56:47 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_syntax_error(char *invalid_token);
static int	check_redirection(t_token *token, char *operator);
static int	check_pipe(t_token *token);
static int	check_next_token(t_token *next_token);

int	check_syntax_errors(t_token *token_head)
{
	t_token	*current_token;

	current_token = token_head;
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

// The pipe can be last character of a cmdline
static int	check_pipe(t_token *token)
{
	if (ft_strncmp(token->value, "|", 1) == 0)
	{
		if (token->next == NULL)
			return (SUCCESS);
		else if (check_next_token(token) == FAILURE)
		{
			print_syntax_error(token->next->value);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

static int	check_redirection(t_token *token, char *operator)
{
	if (ft_strncmp(token->value, operator, 1) == 0)
	{
		if (token->next == NULL)
		{
			print_syntax_error("newline");
			return (FAILURE);
		}
		else if (check_next_token(token) == FAILURE)
		{
			print_syntax_error(token->next->value);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

static int	check_next_token(t_token *token)
{
	if (ft_strncmp(token->next->value, ">", 1) == 0)
		return (FAILURE);
	else if (ft_strncmp(token->next->value, "<", 1) == 0)
		return (FAILURE);
	else if (ft_strncmp(token->next->value, "|", 1) == 0)
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
