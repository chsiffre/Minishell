/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_char_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:48:27 by chsiffre          #+#    #+#             */
/*   Updated: 2023/05/22 14:11:58 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

int check_quote(char *str, int *index, char *charset)
{
	int size;
    int i;

    i = (*index);
	size = 0;
	while (!ft_charset(str[*index], charset) && str[(*index)])
	{
		if (str[(*index)] && (str[(*index)] == '\"' || str[(*index)] == '\''))
		{
			size = skipping_quote(str[i], str, index);
            (*index) = i;
		    return (size + 3);
        }
        if (str[(*index)])
            (*index)++;
	}
    (*index) = i;
	return (0);
}


char *copy_str(int *index, char *str, int len, char *ret)
{
	int i;

    i = 0;
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

int skipping_quote(char c, char *str, int *i)
{
	int size;
	
	size = 0;
	(*i)++;
	while (str[*i] && str[*i] != c)
	{
		(*i)++;
		size++;
	}
	return (size);
}