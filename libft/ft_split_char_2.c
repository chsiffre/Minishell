/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_char_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:48:27 by chsiffre          #+#    #+#             */
/*   Updated: 2023/05/10 13:19:33 by chsiffre         ###   ########.fr       */
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
	while (!ft_charset(str[(*index)], charset) && str[(*index)])
	{
		if (str[(*index)] && str[(*index)] == '\"')
		{
			(*index)++;
			while (str[(*index)] && str[(*index)] != '\"')
			{
				(*index)++;
				size++;
            }
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