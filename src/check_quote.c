/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:12:15 by charles           #+#    #+#             */
/*   Updated: 2023/06/21 14:43:56 by chsiffre         ###   ########.fr       */
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

    i = -1;
	ret = malloc(sizeof (char) * ft_strlen(str) + 1);
    if (!ret)
    {
        return (NULL);
    }
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
            return (replace_quote(str, ret, data));
        else if (str[i] == '$')
            return (replace_all_str(str, ret, i + 1, data));
	}
	return (free(ret), str);
}

char *replace_quote(char *str, char *ret, t_data *data)
{
    ret = resize_quote(str, data);
    if (!ret)
        return (NULL);
    ret = del_quote(str, ret, data);
    return (ret);
}

char *replace_all_str(char *str, char *ret, int i, t_data *data)
{
    if (is_var(str, i , data))
    {
        if (str[i] == '?')
            return (ft_convert_error(str, ret));
        ret = resize_var(str, data);
        if (str[i - 1])
        {
            i = 0;
            while (str[i] != '$')
                ret[data->ind++] = str[i++];
        }
        ret = replace_var(str, ret, &i, data);
        data->ind = 0;
    }
    return (ret);
}

char *ft_convert_error(char *str, char *ret)
{
    int i;
    int y;

    y = 0;
    i = 0;
    free(ret);
    printf("%lu", ft_strlen(str) + ft_int_len(g_error_last) - 1);
    ret = malloc(((ft_strlen(str) - 2) + ft_int_len(g_error_last)) + 1);
    if (!ret)
        return (NULL);
    while (str[i])
    {
        if (str[i] == '$')
        {
            ret = ft_itoa(g_error_last);
            while (ret[y])
                y++;
            i++;
        }
        else
            ret[y++] = str[i];
        i++;
    }
    ret[y] = '\0';
    // printf("%s\n", ret);
    // exit(1);
    return (ret);
}