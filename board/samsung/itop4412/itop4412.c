/*
 * Copyright (C) 2011 Samsung Electronics
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

 /*
#include <common.h>
#include <asm/io.h>
#include <asm/gpio.h>
#include <asm/arch/cpu.h>
#include <asm/arch/mmc.h>
#include <asm/arch/periph.h>
#include <asm/arch/pinmux.h>
#include <usb.h>
*/
#include <common.h>
#include <asm/arch/pinmux.h>
#include <asm/arch/power.h>
#include <asm/arch/clock.h>
#include <asm/arch/gpio.h>
#include <asm/gpio.h>
#include <asm/arch/cpu.h>
#include <dm.h>
#include <power/pmic.h>
#include <power/regulator.h>
#include <power/s5m8767.h>
#include <errno.h>
#include <mmc.h>
#include <usb.h>
#include <usb/dwc2_udc.h>
#include <samsung/misc.h>
//#include "setup.h"

DECLARE_GLOBAL_DATA_PTR;

u32 get_board_rev(void)
{
	return 0;
}

int exynos_power_init(void)
{
	printf("%s\n", __func__);
	
	const char *regulators[] = {
		"VDDIOPERI_28",
		NULL,
	};
#if 0
	if (regulator_list_autoset(regulators, NULL, true))
		printf("Unable to init regulators\n");
#endif
	return 0;
}

static void board_gpio_init(void)
{
#ifdef CONFIG_CMD_USB
	printf("%s\n", __func__);
	/* USB3503 Reset */
	gpio_request(EXYNOS4X12_GPIO_M24, "USB3503 Reset");
	gpio_request(EXYNOS4X12_GPIO_M33, "USB3503 Connect");
	gpio_request(EXYNOS4X12_GPIO_C01, "DM9621");
#if 0	
	gpio_request(EXYNOS4X12_GPIO_B5,"pmic buck1");
	gpio_request(EXYNOS4X12_GPIO_B6,"pmic buck2");
	gpio_request(EXYNOS4X12_GPIO_B7,"pmic buck3");
	gpio_request(EXYNOS4X12_GPIO_M35,"pmic buck4");
	gpio_request(EXYNOS4X12_GPIO_M36,"pmic buck5");
	gpio_request(EXYNOS4X12_GPIO_M37,"pmic buck6");
	
	gpio_direction_output(EXYNOS4X12_GPIO_B5, 1);
	gpio_direction_output(EXYNOS4X12_GPIO_B6, 1);
	gpio_direction_output(EXYNOS4X12_GPIO_B7, 1);
	gpio_direction_output(EXYNOS4X12_GPIO_M35, 1);
	gpio_direction_output(EXYNOS4X12_GPIO_M36, 1);
	gpio_direction_output(EXYNOS4X12_GPIO_M37, 1);
#endif	
//	exynos_pinmux_config(PERIPH_ID_I2C1, PINMUX_FLAG_HS_MODE);
//	exynos_pinmux_config(PERIPH_ID_I2C1, PINMUX_FLAG_HS_MODE);
#endif
}

int exynos_init(void)
{
	printf("%s\n", __func__);
	board_gpio_init();
	return 0;
}

#ifdef CONFIG_USB_GADGET
static int s5pc210_phy_control(int on)
{
	printf("%s\n", __func__);
/*
	struct udevice *dev;
	int ret;

	ret = regulator_get_by_platname("VDD_UOTG_3.0V", &dev);
	if (ret) {
		error("Regulator get error: %d", ret);
		return ret;
	}

	if (on)
		return regulator_set_mode(dev, OPMODE_ON);
	else
		return regulator_set_mode(dev, OPMODE_LPM);
*/
	return 0;
}

struct dwc2_plat_otg_data s5pc210_otg_data = {
	.phy_control	= s5pc210_phy_control,
	.regs_phy		= EXYNOS4X12_USBPHY_BASE,
	.regs_otg		= EXYNOS4X12_USBOTG_BASE,
	.usb_phy_ctrl	= EXYNOS4X12_USBPHY_CONTROL,
	.usb_flags		= PHY0_SLEEP,
};
#endif

#if defined(CONFIG_USB_GADGET) || defined(CONFIG_CMD_USB)
int board_usb_init(int index, enum usb_init_type init)
{
#ifdef CONFIG_CMD_USB
	printf("%s\n", __func__);
	/* Reset*/
	gpio_direction_output(EXYNOS4X12_GPIO_M24, 0);
	gpio_direction_output(EXYNOS4X12_GPIO_M24, 1);
#endif
	return dwc2_udc_probe(&s5pc210_otg_data);
}
#endif

#ifdef CONFIG_BOARD_EARLY_INIT_F
int exynos_early_init_f(void)
{
	return 0;
}
#endif
