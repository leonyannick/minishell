/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:52:25 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/13 16:57:56 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "parser_utils.h"

/* 
	counts the number of commands based on the number of pipes
	appearing in the tokensream. 2 pipes --> 3 commands.
	@argument - token:	linked lsit of tokens
	@return :			number of commands
 */
static unsigned int	ft_cmd_count(t_list *token)
{
	unsigned int	count;

	count = 0;
	while (token)
	{
		if (((t_token *)token->content)->type == PIPE)
			count++;
		token = token->next;
	}
	return (count + 1);
}

/* 
	allocates memory on the heap for a single command and
	initializes with default values.
	@argument:	none
	@return:	pointer on heap to command
 */
static t_command	*ft_create_cmd(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->arguments = NULL;
	cmd->type = PATH;
	cmd->has_in_pipe = false;
	cmd->has_out_pipe = false;
	cmd->in_redir_type = NONE;
	cmd->out_redir_type = NONE;
	cmd->inred_file.path = NULL;
	cmd->inred_file.fd = -1;
	cmd->outred_file = NULL;
	return (cmd);
}

/* 
	creates a linked list based on the amount of amount
	of commands, which is calcualted with the token list.
	@argument - token_head: Head to token linked list 
	@return:				head to linked list, content gets filled later
 */
t_list	*ft_create_cmd_list(t_list *token_head)
{
	int			i;
	t_command	*temp_cmd;
	t_list		*temp_node;
	t_list		*cmd_list;

	cmd_list = NULL;
	if (!token_head)
		return (printf("Tokenhead NULL\n"), NULL);
	i = ft_cmd_count(token_head);
	while (i--)
	{
		temp_cmd = ft_create_cmd();
		if (!temp_cmd)
			return (NULL);
		temp_node = ft_lstnew((void *)temp_cmd);
		if (!temp_node)
			return (NULL);
		ft_lstadd_back(&cmd_list, temp_node);
	}
	return (cmd_list);
}

/* 
	returns the type of a commmand.
	@argument - str:	String of the tokeentype WORD
	@return:			command type (enum)
 */
t_cmd_type	ft_get_cmd_type(char *str)
{
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "pwd") || !ft_strcmp(str, "export")
		|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "env")
		|| !ft_strcmp(str, "exit"))
		return (BUILTIN);
	return (PATH);
}
