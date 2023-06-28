/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 22:44:17 by lucas             #+#    #+#             */
/*   Updated: 2023/06/27 15:11:32 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_exit_error(char *str)
{
	char	*join;

	join = ft_strjoin("bash: exit: ", str);
	join = ft_strjoin(join, " numeric argument required\n");
	write(2, join, ft_strlen(join));
	free(join);
	return (0);
}

static int	ft_is_valid_num(char *command)
{
	int						i;
	unsigned long long int	res;

	i = -1;
	res = 0;
	if (ft_compare_str(command, "-9223372036854775808"))
		return (1);
	if (command[0] == '+')
		i++;
	while (command[++i])
	{
		if (!ft_isdigit(command[i]))
		{
			if (command[i] != '-')
				return (0);
			else
				i++;
		}
		res = (res * 10) + command[i] - '0';
		if (res > LLMAX)
			return (0);
	}
	return (1);
}

void	ft_exit_pack(t_data *data, int code_error)
{
	g_error_last = code_error;
	printf("exit\n");
	ft_to_free(data);
	ft_free_for_end(data);
	exit(g_error_last);
}

int	ft_exit(t_data *data)
{
	if (data->lst->content[1])
	{
		if (data->lst->content[2])
		{
			g_error_last = 1;
			printf("exit\n");
			write(2, "bash: exit: too many arguments\n", 32);
			return (1);
		}
		if (ft_is_valid_num(data->lst->content[1]))
			ft_exit_pack(data, ft_atoi(data->lst->content[1]) % 256);
		else
		{
			g_error_last = 2;
			printf("exit\n");
			ft_exit_error(data->lst->content[1]);
			exit (g_error_last);
		}
	}
	else
		ft_exit_pack(data, g_error_last);
	return (1);
}
