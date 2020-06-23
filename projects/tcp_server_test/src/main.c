/*****************************************************************************
 * wifi_implementation.c
 *****************************************************************************/

#include <common.h>
#include <sys/platform.h>
#include <drivers/pwr/adi_pwr.h>
#include "adi_initialize.h"

void initPower()
{
	if (ADI_PWR_SUCCESS != adi_pwr_Init())
		goto error;

	if (ADI_PWR_SUCCESS != adi_pwr_SetClockDivider(ADI_CLOCK_HCLK, 1u))
		goto error;

	if (ADI_PWR_SUCCESS != adi_pwr_SetClockDivider(ADI_CLOCK_PCLK, 1u))
		goto error;

	return;
error:
	printf("ERROR INITIALIZING POWER\n");
	exit(1);
}

int32_t wifi_test();
#include "core_cm3.h"
int main(int argc, char *argv[])
{
	/**
	 * Initialize managed drivers and/or services that have been added to
	 * the project.
	 * @return zero on success
	 */
	adi_initComponents();
	initPower();

	SCnSCB->ACTLR |= SCnSCB_ACTLR_DISDEFWBUF_Msk;

	wifi_test();

	while (1);

	return 0;
}
