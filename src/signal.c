/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:51:04 by luhumber          #+#    #+#             */
/*   Updated: 2023/05/30 17:20:25 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_ctrl(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		printf("\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGTERM)
		exit (0);
}

void	ft_ctrl_fork(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		printf("\n");
		rl_replace_line("", 0);
	}
	else if (signal == SIGTERM)
		exit (0);
	else
	{
		write(2, "Quit (core dumped)\n", 20);
		return ;
	}
}

void	ft_here_sig(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		printf("\n");
		rl_replace_line("", 0);
		exit(1);
	}
}
