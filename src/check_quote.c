/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:12:15 by charles           #+#    #+#             */
/*   Updated: 2023/06/05 17:01:50 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char **check_quotes(char **strs, t_data *data)
{
    int i;
    
    i = 0;
    while (strs[i])
    {
        strs[i] = is_quote(strs[i], data);
        i++;
    }
    strs[i] = NULL;
    return (strs);
}

char *is_quote(char *str, t_data *data)
{
	int	i;
	char *ret;

	ret = NULL;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
            ret = resize_quote(str, data);
            if (!ret)
                return (NULL);
            ret = del_quote(str, ret, data);
            return (ret);
        }
        else if (str[i] == '$')
        {
            if (is_var(str, i , data))
            {   ret = resize_var(str, data);
                ret = replace_var(str, ret, &i, data);
                data->ind = 0;
            }
            return (ret);
        } 
	}
	return (str);
}

char *del_quote(char *str, char *ret, t_data *data)
{
	int i;
    int quote;

    quote = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == '\"' || str[i] == '\'')
        {
            quote = str[i++];
            while (str[i] && str[i] != quote)
            {
                if (str[i] == '$' && if_expand(str) && is_var(str, i, data))
                    ret = replace_var(str, ret, &i, data);
                else if (str[i])
                    ret[data->ind++] = str[i++];
            }
        }
        else
            ret[data->ind++] = str[i++];
    }
    ret[data->ind] = '\0';
	return (ret);
}

char    *resize_var(char *str, t_data *data)
{
    t_env   *tmp;
    int i;
    int new_size;
 
    i = 0;
    new_size = 0;
    tmp = data->env;
    
    while (str[i] && str[i] != '$')
    {
        i++;
        new_size++;
    }
    i++;
    while (tmp)
    {
        if (ft_compare_var(str, tmp->name, i))
        {
            i = -1;
            while (tmp->value[++i])
                new_size++;
            break;
        }
        tmp = tmp->next;
    }
    return (malloc(sizeof(char ) * new_size + 1));
}

char *resize_quote(char *str, t_data *data)
{
    int i;
    int new_size;
    char quote;
    
    i = -1;
    quote = 0;
    new_size = 0;
    while (str[++i])
    {
        if (str[i] == '\'' || str[i] == '\"')
        {
            quote = str[i++];
            while (str[i] && str[i] != quote)
            {
                if (str[i] == '$' && if_expand(str) && is_var(str, i, data))
                    new_size += var_exist(str, &i, data);
                else if (str[i] == '$' &&  if_expand(str) && !is_var(str, i, data))
                    while (str[i] && ft_isalnum(str[i]))
                        i++;
                else
                {
                    new_size++;
                    i++;
                }
            }
        }
        else
            new_size++;
    }
    return (malloc(sizeof (char) * new_size + 1));
}

// char *copy_quote(char *ret, char *str, t_data *data, int *i)
// {
//     char quote;

//     quote = str[*i];
//     (*i)++;
//     while (str[(*i)] != quote)
//     {
//         if ()
//         ret[*y++] = str[*i++];
//     }
//     return (ret);
// }