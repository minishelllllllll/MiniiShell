/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_send.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:23:37 by marvin            #+#    #+#             */
/*   Updated: 2025/05/23 18:23:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd *ft_send(t_var *data, t_cmd *cmd)
{
    t_cmd *new_node;
    t_cmd *current;

    // Create new command node
    new_node = malloc(sizeof(t_cmd));
    if (!new_node)
        return (NULL);

    // Allocate and copy command arguments
    new_node->full_cmd = malloc((data->l + 1) * sizeof(char *));  // +1 for NULL terminator
    if (!new_node->full_cmd)
    {
        free(new_node);
        return (NULL);
    }
    
    // Copy the command arguments
    for (int i = 0; i < data->l; i++)
    {
        new_node->full_cmd[i] = data->s[i];  // Transfer ownership
    }
    new_node->full_cmd[data->l] = NULL;  // NULL terminate the array
    
    // Set file descriptors
    new_node->out_file = data->out_file;
    new_node->in_file = data->in_file;
    new_node->next = NULL;

    // If this is the first command node
    if (!cmd)
        return (new_node);

    // Find the last node and append
    current = cmd;
    while (current->next)
        current = current->next;
    current->next = new_node;

    return (cmd);  // Return the head of the list
}