/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramondo <jramondo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 14:46:22 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/02 20:48:33 by jramondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new_s;

	new_s = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (new_s == NULL)
		return (NULL);
	ft_strlcpy(new_s, s, ft_strlen(s) + 1);
	return (new_s);
}
