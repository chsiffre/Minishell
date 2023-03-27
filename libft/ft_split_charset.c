/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 21:01:54 by chsiffre          #+#    #+#             */
/*   Updated: 2022/11/26 18:26:35 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	int		i;

	len = 0;
	i = 0;
	while (ft_charset(str[*index], charset))
		(*index)++;
	while (!ft_charset(str[*index + len], charset) && str[*index + len])
		len++;
	ret = malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	while (i < len)
	{
		ret[i] = str[*index];
		i++;
		(*index)++;
	}
	ret[i] = 0;
	return (ret);
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
