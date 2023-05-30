/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:50:45 by chsiffre          #+#    #+#             */
/*   Updated: 2023/05/30 17:15:10 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int var_exist(char *str, int *i, t_data *data)
{
    t_env *tmp;

    tmp = data->env;
    while (tmp)
    {
        if (ft_compare_var(str, tmp->name, *i))
        {
            //printf("first char key : %c , value :%s\n", str[*i], tmp->value);
            return (ft_strlen(tmp->value));
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
	return (1);
}