/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 21:01:54 by chsiffre          #+#    #+#             */
/*   Updated: 2023/06/04 18:54:51 by charles          ###   ########.fr       */
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
	char c;

	c = 0;
	count = 0;
	i = 0;
	while (str[i])
	{
		while (ft_charset(str[i], charset) && str[i])
			i++;
		if (!str[i])
			break;
		if (str[i] == '\"' || str[i] == '\'')
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
			i++;
			count++;
		}
		else
			count++;
		skiping_next(str, charset, &i, &count);
	}
	return (count + 1);
}

void	skiping_next(char *str, char *charset, int *i, int *count)
{
	char c;

	c = 0;
	if (str[*i] == '\'' || str[*i] == '\"')
	{
		c = str[(*i)++];
		while (str[(*i)] != c && str[*i])
			(*i)++;
		(*i)++;
		(*count)++;
	}
	else
	{
		while (!ft_charset(str[*i], charset) && str[*i] && str[*i] != '\"' && str[*i] != '\'')
			(*i)++;
		if (str[*i + 1] && !ft_charset(str[*i], charset))
			(*count)++;
	}
}

char	*give_memory(char *str, char *charset, int *index, int i_str)
{
	int		len;
	char	*ret;

	ret = NULL;
	len = 0;
	len = check_space(str, index, charset, i_str);
	if (len != 0)
	{
		if (i_str == 1)
			while (ft_charset(str[*index], charset))
				(*index)++;
		else
			while (ft_charset(str[*index], charset) && str[(*index) + 1] != '\"' && str[(*index) + 1] != '\'')
				(*index)++;
		return (copy_str(index, str, len ,ret));
	}
	len = check_quote(str, index, charset);
	if (len != 0)
		return (copy_str(index, str, len, ret));
	while (ft_charset(str[*index], charset))
		(*index)++;
	while (!ft_charset(str[*index + len], charset) && str[*index + len] &&
	str[*index + len] != '\'' && str[*index + len] != '\"')
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
		strs[i] = give_memory(str, charset, &j, i);
		i++;
	}
	strs[i] = 0;
	return (strs);
}
