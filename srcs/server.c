

#include "../incs/minitalk.h"

#include "../incs/minitalk.h"

void ft_handle_signal(int sig, siginfo_t *siginfo, void *context)
{
    static int	bit = 0;
    static int	i = 0;

    (void)context;

    if (sig == SIGUSR1)
        i |= (0x01 << bit);
    bit++;
    if (bit == 8)
    {
        write(1, &i, 1);
        if (i == 10)
            ft_print_error(S_CHEV);
        bit = 0;
        i = 0;
    }
}

int main(void)
{
    pid_t				pid;
    struct sigaction	sa;

    pid = getpid();
    ft_putendl_fd(S_WLC, 1);
    ft_printf(S_PID, pid);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = ft_handle_signal;
    sigemptyset(&sa.sa_mask);

    while (1)
    {
        if (sigaction(SIGUSR1, &sa, NULL) != 0 || sigaction(SIGUSR2, &sa, NULL) != 0)
        {
            perror("Error setting up signal handler");
            return (1);
        }

        if (pause() == -1)
        {
            perror("Error in pause");
            return (1);
        }
    }

    return (0);
}
