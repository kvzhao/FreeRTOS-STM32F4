#include "MEMS.h"

void MEMS_Configuration()
{
    lis3dsh_init();
    lis3dsh_set_OutputDataRate(LIS3DSH_ODR_400_HZ);
    lis3dsh_AxesEnable(LIS3DSH_XYZ_ENABLE);
}

