

#include "../incs/minitalk.h"

int main(int ac, char **av)
{
    int	i;
    int	server_pid;

    i = 0;
    server_pid = ft_atoi(av[1]);
    if (ac == 3 && ft_is_str_digit(av[1]) && server_pid > 1)
    {
        while (av[2][i])
        {
            ft_send_bit(server_pid, av[2][i], 200);
            i++;
        }
        ft_send_bit(server_pid, 10, 200);
    }
    else
    {
        ft_print_error("Error");
        ft_print_args_error();
        return (1);
    }
    return (0);
}
