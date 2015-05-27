#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <modbus.h>

int main()
{
    modbus_t *ctx = modbus_new_tcp("127.0.0.1", 12345);

    modbus_set_debug(ctx, true);

    int socket = modbus_tcp_listen(ctx, 1);
    modbus_tcp_accept(ctx, &socket);

    uint8_t bits[8] = {0, 1, 0, 1, 0, 1, 0, 1};
    uint8_t bits_input[8] = {1, 0, 1, 0, 1, 0, 1, 0};
    uint16_t input_registers[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    uint16_t registers[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    modbus_mapping_t mapping = {
        sizeof(bits), sizeof(bits_input), sizeof(input_registers), sizeof(registers),
        bits, bits_input, input_registers, registers
    };

    for (;;) {
        uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
        int rc = modbus_receive(ctx, query);
        if (rc == -1) {
            fprintf(stderr, "failed to receive: %s\n", modbus_strerror(errno));
            break;
        }
        printf("received query of length %d, sending reply.\n", rc);

        rc = modbus_reply(ctx, query, rc, &mapping);
        for (int i = 0; i < sizeof(bits); ++i) {
            printf("i = %d, b = %x, bi = %x\n", i, bits[i], bits_input[i]);
        }
        if (rc == -1) {
            fprintf(stderr, "failed to reply: %s\n", modbus_strerror(errno));
            break;
        }
    }

    printf("Quit the loop: %s\n", modbus_strerror(errno));
    close(socket);

    modbus_free(ctx);

    return 0;
}
