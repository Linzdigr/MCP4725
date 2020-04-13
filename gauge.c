#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "mcp4725.h"
#include <time.h>

int main (int arcgc, char **argv);

int main(int argc, char **argv)
{
    struct mcp4725 channel1;
    time_t start, end;
    float value;

    if (getuid()) {
        printf ("This program needs to be run as root.\n");
        exit (1);
    }

    printf ("MCP4725 test program. Enter a value in volts, \n-1 for power down (1K), -2 for power down (500K), -3 for normal operation or \n-4 to exit\n");

    channel1.i2c_id = 0x60;         // The id of the 4725 - use sudo i2cdetect -y 1
    channel1.fullscale = 4.735;     // Full scale OP voltage,
    mcp4725_init(&channel1);

    do {
        printf ("value? ");
        scanf("%f", &value);
        if (value >= 0 && mcp4725_setvolts(&channel1, value)) printf("Error: %s\n", channel1.error);
        if (value == -1) mcp4725_setmode(&channel1, MODE_1K);
        if (value == -2) mcp4725_setmode(&channel1, MODE_500K);
        if (value == -3) mcp4725_setmode(&channel1, MODE_NORMAL);
    }
    while (value >= -3);
        
    mcp4725_close(&channel1);

}