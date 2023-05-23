/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:37:12 by lucas             #+#    #+#             */
/*   Updated: 2023/05/22 22:21:58 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_compare_str(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if ((s1[i] != s2[i]) || (s2[i] != s1[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_lsize(t_lst *lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

void	ft_list_to_tab(t_data *data, t_lst *lst)
{
	t_lst	*tmp;
	int		i;
	int		j;

	tmp = lst;
	i = 0;
	data->cmd = malloc(sizeof(char *) * (ft_lsize(tmp) + 1));
	if (data->cmd == NULL)
		ft_error(data, "malloc error\n", 1);
	while (tmp)
	{
		j = 0;
		data->cmd[i] = malloc(sizeof(char) * ft_strlen((*tmp->content)));
		if (data->cmd[i])
			ft_error(data, "malloc error\n", 1);
		while (tmp->content[j])
		{
			data->cmd[i][j] = (*tmp->content[j]);
			j++;
		}
		i++;
		tmp = tmp->next;
	}
	data->cmd[i] = NULL;
}
