/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:12:15 by charles           #+#    #+#             */
/*   Updated: 2023/05/31 15:24:26 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char **check_quote(char **strs, t_data *data)
{
    int i;

    i = 0;
    while (strs[i])
    {
        strs[i] = is_quote(strs[i]);
    }
    return (strs);
}

char *is_quote(char *str)
{
	int	i;
	char *ret;

	ret = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
            ret = resize_quote(ret, str);
            if (!ret)
                return (NULL);
            ret = del_quote(ret, str);
            return (ret);
        }    
		i++;
	}
	return (str);
}

char *del_quote(char *str,char *ret)
{
	int i;
    int y;

    y = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == '\"' || str[i] == '\'')
        {
            ret = copy_quote(ret, str, &y, &i);
        }
        i++;
    }
    ret[y] = NULL;
	return (ret);
}

char *resize_quote(char *ret, char *str)
{
    int i;
    int new_size;
    char quote;
    
    i = 0;
    quote = 0;
    while (str[i])
    {
        if (str[i] == '\'' || str[i] == '\"')
        {
            quote = str[i];
            i++;
            while (str[i++] != quote)
                new_size++;
        }
        else
            new_size++;
        i++;
    }
    return (malloc(sizeof (char) * new_size + 1));
}

char *copy_quote(char *ret, char *str, int *y, int *i)
{
    char quote;

    quote = str[*i];
    (*i)++;
    while (str[*i] != quote)
    {
        ret[*y++] = str[*i++];
        if (quote == '\"' && str[*i] == '$')
        {
            ret = ft_expand(str);
        }
    }
    return (ret);
}