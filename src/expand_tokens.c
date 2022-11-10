/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:34:32 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/11/10 01:32:15 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// // TODO: Check for ' and ", and remove then
// // TODO: Replace $VARIABLES
// // TODO: Remove empty variables when they are alone in a token
// // NOTE: Default variable value: ""

// static t_token	*expand_token(t_token *token);
// static void		check_single_col(char c, int *single_col);
// static int		get_var_count(char *data);
// static char		**get_env_vars(char *data);
// static int		check_var_chars(char *data, int i);
// static char		*get_var_name(char *data, int *i, t_token *token_head);

// t_token	*expand_tokens(t_token *token_head)
// {
// 	t_token	*current_token;

// 	current_token = token_head;
// 	while (current_token != NULL)
// 	{
// 		current_token = expand_token(current_token);
// 		current_token = current_token->next;
// 	}
// 	return (token_head);
// }

// // TODO: Create a new token value without quotes and with the vars
// // TODO: Last env_var will be NULL
// static t_token	*expand_token(t_token *token)
// {
// 	char	**env_vars;

// 	env_vars = get_env_vars(token->value);
// 	// if (env_vars == NULL)
// 		// Do something
// }

// static char	**get_env_vars(char *data, t_token *token_head)
// {
// 	int		var_count;
// 	char	**env_vars;
// 	int		i;

// 	var_count = get_var_count(data);
// 	if (var_count == 0)
// 		return (NULL);
// 	env_vars = malloc(sizeof(char *) * (var_count + 1));
// 	if (env_vars == NULL)
// 		exit_error_token(token_head);
// 	i = 0;
// 	while (data[i] != '\0')
// 	{

// 	}
// 	return (env_vars);
// }

// static char	*get_var_name(char *data, int *i, t_token *token_head)
// {
// 	char	*var_name;
// 	int		single_col;

// 	single_col = 0;
// 	while (data[*i] != '\0')
// 	{
// 		check_single_col(data[*i], &single_col);
// 		if (data[*i] == '$')
// 		{
// 			while (ft_isalnum(data[*i]) != 0)
// 			{

// 			}
// 		}
// 	}
// }

// static int	get_var_count(char *data)
// {
// 	int	i;
// 	int	count;
// 	int	single_col;

// 	i = 0;
// 	count = 0;
// 	single_col = FALSE;
// 	while (data[i] != '\0')
// 	{
// 		check_single_col(data[i], &single_col);
// 		if (data[i] == '$' && single_col == FALSE)
// 		{
// 			if (check_var_chars(data, i) == SUCCESS)
// 				count++;
// 		}
// 		i++;
// 	}
// 	return (count);
// }

// static int	check_var_chars(char *data, int i)
// {
// 	if (ft_isalnum(data[i+ 1]) != 0)
// 		return (SUCCESS);
// 	else if (data[i + 1] == '_')
// 		return (SUCCESS);
// 	else if (data[i + 1] == '?')
// 		return (SUCCESS);
// }

// static void	check_single_col(char c, int *single_col)
// {
// 	if (c == '\'')
// 	{
// 		if (*single_col == TRUE)
// 			*single_col = FALSE;
// 		else
// 			*single_col = TRUE;
// 	}
// }

// static char	*get_expanded_token(t_token *token)
// {
// 	int		single_col;
// 	char	*env_var;
// 	char	*expanded_token;
// 	int		start;
// 	int		i;
// 	int		var_end;

// 	single_col = FALSE;
// 	start = 0;
// 	i = start;
// 	while (token->value[i] != '\0')
// 	{
// 		check_single_col(token->value[i], &single_col);
// 		if (check_var(token->value, i) == TRUE)
// 		{
// 			start = 
// 			var_end = get_var_end(token->value, i);
// 			expanded_token = ft_substr(token->value, start, i - start + 1);
// 		}
// 		i++;
// 	}
// }

// // TERRIBLE NAME
// static char	*get_expanded_token_so_far(const char *data, int start, int end);

// static char *join_expanded_token_with_var(char *expanded_token, char *var_name);

// static int	check_var(const char *data, int i)
// {
// 	if (data[i] == '$')
// 	{
// 		if (ft_isalnum(data[i + 1]))
// 			return (TRUE);
// 		else if(data[i + 1] == '_')
// 			return (TRUE);
// 		else if (data[i + 1] == '?')
// 			return (TRUE);
// 	}
// 	return (FALSE);
// }

// // Return the last index of the variable name
// static int	get_var_end(const char *data, int start)
// {
// 	int	i;

// 	i = start + 1;
// 	if (data[i] == '?')
// 		return (i);
// 	while (data[i] != '\0')
// 	{
// 		if (ft_isalnum(data[i]) != 0)
// 			break ;
// 		else if (data[i] != '_')
// 			break ;
// 		i++;
// 	}
// 	return (i - 1);
// }
