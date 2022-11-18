/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:51:56 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/11/18 18:27:12 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: Change token to genetic list
// TODO: Change env_vars to a hashtable
// void	expand_tokens(t_token token_head, t_list env_vars)
// {
// 	
// }

/* NOTE:
 * Get each individual token
 * Create a sublist with that token, with the string and the expanded vars
 * Join the whole list to a single str and assign it to that token
 * Need to expand the ~ too
*/
