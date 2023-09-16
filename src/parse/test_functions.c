
#include <minishell.h>

//void print_whole_list(t_list *list)
//{
//	t_list *temp;
//	temp = list;
//	printf("\n\n");
//	while (temp)
//	{
//		printf("--------------------\n");
//		print_t_exec(temp);
//		temp = temp->next;
//	}
//}

//// somehow moves the pointers so if you use this expect leaks xxxx <3
// void print_t_exec(t_list *list)
// {
//    int node_amnt = 0;
//    while (list->exec)
//    {
//        t_exec  *exec =  list->exec;
//        t_rdr   *rdr = list->exec->rdr;
//        t_str   *cmd = list->exec->cmd;
//        t_str   *hd = NULL;
//        printf("\nnode %d\n", node_amnt);
//        printf("[\n");
//        printf("CMD: ");
//		if (exec->subshell)
//		{
//			printf("-------SUBSHELL----------- ");
//			print_t_exec(list);
//			printf("---END SUBSHELL----------- ");
//		}
//        while (cmd)
//        {
//            printf("%s, ", cmd->str);
//            cmd = cmd->next;
//        }
//        printf("\n");
//        printf("RDR: ");
//        while (rdr)
//        {
//            if (rdr->type == HEREDOC || rdr->type == HEREDOC_NO_EXP)
//            {
//                if (hd)
//                    printf("\n(WARNING! 2 heredocs found but the print function will only display the last ones contents)\n");
//                if (rdr->type == HEREDOC)
//                    printf("{HEREDOC} [%d], ", rdr->type);
//                else
//                    printf("{HEREDOC_NO_EXP} [%d], ", rdr->type);
//                hd = rdr->file;
//            }
//            else
//                printf("{%s} [%d], ", rdr->file->str, rdr->type);
//            rdr = rdr->next;
//        }
//        if (hd)
//            printf("\nHEREDOC contents: ");
//        while (hd)
//        {
//            printf("{%s}, ", hd->str);
//            hd = hd->next;
//        }
//        hd = NULL;
//        node_amnt++;
//        printf("\n]\n\n");
//        list->exec = list->exec->next;
//    }
// }

////void print_whole_list(t_list *list)
////{
////    t_list *temp;
////    temp = list;
////    printf("\n\n");
////    while (temp)
////    {
////        printf("--------------------\n");
////        print_t_exec(temp, temp->input);
////        temp = temp->next;
////    }
////}

//void	print_class(int	num)
//{
//	//norm error not to forget to remove
//	if (num == WORD)
//		printf("word        : ");
//	else if (num == REDIRLEFT)
//		printf("redir left  : ");
//	else if (num == REDIRRIGHT)
//		printf("redirright  : ");
//	else if (num == HEREDOC)
//		printf("append left : ");
//	else if (num == APPEND)
//		printf("append right: ");
//	else if (num == PIPESYMBOL)
//		printf("pipe        : ");
//	else
//		printf("BLANK %d: ", num);
//}

//void print_test(t_list *list, char *input)
//{
//	int	i = 0; //remove func later
//	int	num;

//	while (input[i])
//	{
//		while (input[i] == ' ')
//			i++;
//		num = list->token[i];
//		print_class(list->token[i]);
//		while (list->token[i] == num && input[i])
//		{
//			printf("%c", input[i]);
//			i++;
//		}
//		printf("\n");
//	}
//}

void	print_tokens(t_list *list, int len)
{
	int i = 0;
	//printf("len = %d\n", len);
	while (i < len)
	{
		printf("[%d]", list->token[i]);
		i++;
	}
	printf("\n");
}
