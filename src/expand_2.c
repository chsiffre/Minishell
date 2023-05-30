/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:50:45 by chsiffre          #+#    #+#             */
/*   Updated: 2023/05/30 13:51:25 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int var_exist(char *str, t_data *data)
{
    t_env *tmp;

    tmp = data->env;
    str++;
    while (tmp)
    {
        if (ft_compare_var(str, tmp->name))
            return (ft_strlen(tmp->name));
        tmp = tmp->next;
    }
    return (0);
}

int	ft_compare_var(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if ((s1[i] != s2[i]) || (s2[i] != s1[i]))
			return (0);
		i++;
	}
	return (1);
}