/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:37:12 by lucas             #+#    #+#             */
/*   Updated: 2023/04/12 11:37:18 by luhumber         ###   ########.fr       */
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
	while (tmp)
	{
		j = 0;
		data->cmd[i] = malloc(sizeof(char) * ft_strlen((*tmp->content)));
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
