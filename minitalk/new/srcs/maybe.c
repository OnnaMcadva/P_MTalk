static void handle_signal(int sig, siginfo_t *info, void *context) {
    static unsigned char buf[5];  // Буфер для UTF-8
    static int byte_pos = 0;      // Текущая позиция в буфере
    static int bit_pos = 0;
    static unsigned char c = 0;

    // Сборка байта (как у вас)
    c |= (sig == SIGUSR1) << (7 - bit_pos);
    bit_pos++;

    if (bit_pos == 8) {
        buf[byte_pos++] = c;
        bit_pos = 0;
        c = 0;

        if ((buf[0] & 0x80) == 0) {          // ASCII (1 байт)
            buf[1] = '\0';
            ft_putstr_fd((char*)buf, 1);
            byte_pos = 0;
        }
        else if ((buf[0] & 0xE0) == 0xC0) {  // 2 байта (кириллица)
            if (byte_pos == 2) {
                buf[2] = '\0';
                ft_putstr_fd((char*)buf, 1);
                byte_pos = 0;
            }
        }
        // ... (аналогично для 3 и 4 байтов)
    }
    kill(info->si_pid, SIGUSR1);
}
