/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:45:19 by charles           #+#    #+#             */
/*   Updated: 2023/07/03 10:07:51 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dest;
	int		count;

	i = -1;
	count = ft_strlen(s) + 1;
	dest = malloc(count * sizeof(char));
	if (!dest)
		return (NULL);
	while (s[++i])
		dest[i] = s[i];
	dest[i] = '\0';
	return (free((char *) s), dest);
}
