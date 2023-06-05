/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:50:45 by chsiffre          #+#    #+#             */
/*   Updated: 2023/06/05 16:43:15 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int var_exist(char *str, int *i, t_data *data)
{
    t_env *tmp;

    tmp = data->env;
    if (str[*i] == '$')
        (*i)++;
    while (tmp)
    {
        if (ft_compare_var(str, tmp->name, *i))
        {
            while (str[*i] && str[*i] != '\'' && str[*i] != '\"')
                (*i)++;
            (*i)++;
            return ((int) ft_strlen(tmp->value));
        }
        tmp = tmp->next;
    }
    return (0);
}

int is_var(char *str, int i, t_data *data)
{
    t_env *tmp;

    tmp = data->env;
    if (str[i] == '$')
        (i)++;
    while (tmp)
    {
        if (ft_compare_var(str, tmp->name, i))
        {
            // printf("%s\n", tmp->name);
            // exit(1);
            while (str[i] && str[i] != '\'' && str[i] != '\"')
                (i)++;
            return ((int) ft_strlen(tmp->value));
        }
        tmp = tmp->next;
    }
    return (0);
}

int	ft_compare_var(char *s1, char *s2, int i)
{
    int y;

    y = 0;
	while (s1[i] && s2[y])
	{
		if ((s1[i] != s2[y]))
			return (0);
		i++;
        y++;
	}
    if (!s1[i] && s2[y] == '=')
        return (1);
    else if (!s1[i] && !s2[y])
        return (1);
    else
	    return (0);
}

int if_expand(char *str)
{
    int ind;
    char quote;
    char f_quote;

    f_quote = 0;
    quote = 0;
    ind = -1;
    while (str[++ind])
    {
        if (str[ind] == '\"' || str[ind] == '\'')
        {
            if (f_quote == 0)
                f_quote = str[ind];
            quote = str[ind];
            while (str[++ind] != quote)
            {
                if (str[ind] == '$' && f_quote == '\"')
                    return (1);
            }
        }
        else if (str[ind] == '$')
            return (1);
    }
    return (0);
}