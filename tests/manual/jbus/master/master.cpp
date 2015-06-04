#include <modbus.h>

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int main()
{
    modbus_t* ctx = modbus_new_rtutcp("127.0.0.1", 12345);
    if (!ctx) {
        fprintf(stderr, "failed to create modbus context: %s\n", modbus_strerror(errno));
        return 1;
    }
    modbus_set_debug(ctx, true);

    if (modbus_connect(ctx) == -1) {
        fprintf(stderr, "connection failed: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        return 1;
    }

    uint8_t output[8];
    if (modbus_read_bits(ctx, 0, sizeof(output), output) == -1) {
        fprintf(stderr, "reading bits failed: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        return 1;
    }
    for (int i = 0; i < (int)sizeof(output); ++i) {
        fprintf(stderr, "i = %d, c = %x\n", i, output[i]);
        output[i] = !output[i];
    }
    printf("now writing:\n");
    for (int i = 0; i < (int)sizeof(output); ++i) {
        fprintf(stderr, "i = %d, c = %x\n", i, output[i]);
    }
    if (modbus_write_bits(ctx, 0, sizeof(output), output) == -1) {
        fprintf(stderr, "writing bits failed: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        return 1;
    }
    printf("reading back:\n");
    if (modbus_read_bits(ctx, 0, sizeof(output), output) == -1) {
        fprintf(stderr, "reading bits failed: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        return 1;
    }
    printf("got:\n");
    for (int i = 0; i < (int)sizeof(output); ++i) {
        fprintf(stderr, "i = %d, c = %x\n", i, output[i]);
    }

    modbus_free(ctx);

    return 0;
}
