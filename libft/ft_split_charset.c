/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 21:01:54 by chsiffre          #+#    #+#             */
/*   Updated: 2023/05/09 16:51:22 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	get_ac(char *str, char *charset)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (ft_charset(str[i], charset))
			i++;
		if (!ft_charset(str[i], charset) && str[i])
		{
			if (str[i] && str[i] == '\"')
			{
				i++;
				while (str[i] && str[i] != '\"')
					i++;
			}
			count++;
			while (!ft_charset(str[i], charset) && str[i])
				i++;
		}
	}
	return (count + 1);
}

char	*give_memory(char *str, char *charset, int *index)
{
	int		len;
	char	*ret;
	ret = NULL;

	len = 0;
	while (ft_charset(str[*index], charset))
		(*index)++;
	len = check_quote(str, index, charset);
	if (len != 0)
		return (copy_str(index, str, len, ret));
	while (!ft_charset(str[*index + len], charset) && str[*index + len])
		len++;
	return (copy_str(index, str, len, ret));
}

char	**ft_split_charset(char *str, char *charset)
{
	int		i;
	int		nb_str;
	char	**strs;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	nb_str = get_ac(str, charset);
	strs = malloc(nb_str * sizeof(char *));
	if (!strs)
		return (NULL);
	while (i < (nb_str - 1))
	{
		strs[i] = give_memory(str, charset, &j);
		i++;
	}
	strs[i] = 0;
	return (strs);
}
