/* Copyright (c) 2010, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include <linux/io.h>
#include <linux/module.h>
#include <mach/msm_iomap.h>
#include "gpiomux.h"
#include "proc_comm.h"

struct msm_gpiomux_config msm_gpiomux_configs[GPIOMUX_NGPIOS] = {};

void __msm_gpiomux_write(unsigned gpio, gpiomux_config_t val)
{
	unsigned tlmm_config  = (val & ~GPIOMUX_CTL_MASK) |
				((gpio & 0x3ff) << 4);
	unsigned tlmm_disable = 0;
	int rc;

	rc = msm_proc_comm(PCOM_RPC_GPIO_TLMM_CONFIG_EX,
			   &tlmm_config, &tlmm_disable);
	if (rc)
		pr_err("%s: unexpected proc_comm failure %d: %08x %08x\n",
		       __func__, rc, tlmm_config, tlmm_disable);
}
