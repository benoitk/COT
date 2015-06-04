#include <modbus.h>

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

template<typename B, typename ReadFN>
void read(modbus_t *ctx, int address, B *buffer, int N, ReadFN readfn)
{
    printf("reading 0x%04x + %d\n", address, N);
    if (readfn(ctx, address, N, buffer) == -1) {
        fprintf(stderr, "read failed: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        exit(1);
    }
    for (int i = 0; i < N; ++i) {
        printf("0x%04x = %d\n", address + i, buffer[i]);
    }
}

void writeNegated(modbus_t *ctx, int address, uint8_t *buffer, int N)
{
    printf("writing negated values to 0x%04x + %d\n", address, N);
    uint8_t outputBitsToWrite[N];
    for (int i = 0; i < (int)sizeof(buffer); ++i) {
        outputBitsToWrite[i] = !buffer[i];
    }
    if (modbus_write_bits(ctx, address, sizeof(outputBitsToWrite), outputBitsToWrite) == -1) {
        fprintf(stderr, "writing bits failed: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        exit(1);
    }
}

int main()
{
    modbus_t *ctx = modbus_new_tcp("192.168.1.10", 502);
    if (!ctx) {
        fprintf(stderr, "failed to create modbus context: %s\n", modbus_strerror(errno));
        return 1;
    }
    modbus_set_debug(ctx, true);
    modbus_set_slave(ctx, 1);

    if (modbus_connect(ctx) == -1) {
        fprintf(stderr, "connection failed: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        return 1;
    }


    {
        uint8_t inputBits[2];
        read(ctx, 0x0100, inputBits, 2, modbus_read_input_bits);
    }
    {
        uint8_t outputBits[4];
        read(ctx, 0x0200, outputBits, 4, modbus_read_bits);
        for (int i = 0; i < 2; ++i) {
            writeNegated(ctx, 0x0200, outputBits, 4);
            read(ctx, 0x0200, outputBits, 4, modbus_read_bits);
        }
    }

    {
        uint8_t voltageOutputBits[2];
        read(ctx, 0x0300, voltageOutputBits, 2, modbus_read_bits);
        for (int i = 0; i < 2; ++i) {
            writeNegated(ctx, 0x0300, voltageOutputBits, 2);
            read(ctx, 0x0300, voltageOutputBits, 2, modbus_read_bits);
        }
    }

    {
        int loop;
        uint16_t *loopRegisters = reinterpret_cast<uint16_t*>(&loop);
        read(ctx, 0x0400, loopRegisters, 2, modbus_read_registers);
        printf("loop = %d\n", loop);
    }

    modbus_free(ctx);

    return 0;
}
