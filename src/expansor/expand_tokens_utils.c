/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 18:40:00 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/11/24 18:54:32 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		get_var_length(char *data);
static char		*get_var_data(char *data, int length, t_env_var **envl);

int	expand_var_data(char *data, int length, t_slist **data_list,
		t_env_var **envl)
{
	int		var_length;
	char	*var_data;

	if (length > 0)
	{
		data_list = split_token_data(data, length, data_list);
	}
	var_length = get_var_length(&data[length]);
	var_data = get_var_data(&data[length], var_length, envl);
	data_list = append_to_slist(data_list, var_data);
	return (var_length);
}

t_slist	**split_token_data(char *data, int length, t_slist **data_list)
{
	char	*sub_data;

	sub_data = ft_substr(data, 0, length);
	data_list = append_to_slist(data_list, sub_data);
	return (data_list);
}

static int	get_var_length(char *data)
{
	int	i;

	i = 1;
	while (data[i] != '\0')
	{
		if (ft_isalnum(data[i]) == FALSE && data[i] != '_')
			return (i);
		i++;
	}
	return (i);
}

// Return "$" if $ is not followed by valid chars
static char	*get_var_data(char *data, int length, t_env_var **envl)
{
	char	*var_name;
	char	*var_data;

	if (length == 1)
		return (ft_strdup("$"));
	var_name = ft_substr(data, 1, length - 1);
	var_data = search_env_var(envl, var_name);
	free(var_name);
	return (var_data);
}
