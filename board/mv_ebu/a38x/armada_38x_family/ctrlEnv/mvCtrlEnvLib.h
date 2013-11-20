/*******************************************************************************
   Copyright (C) Marvell International Ltd. and its affiliates

   This software file (the "File") is owned and distributed by Marvell
   International Ltd. and/or its affiliates ("Marvell") under the following
   alternative licensing terms.  Once you have made an election to distribute the
   File under one of the following license alternatives, please (i) delete this
   introductory statement regarding license alternatives, (ii) delete the two
   license alternatives that you have not elected to use and (iii) preserve the
   Marvell copyright notice above.

********************************************************************************
   Marvell Commercial License Option

   If you received this File from Marvell and you have entered into a commercial
   license agreement (a "Commercial License") with Marvell, the File is licensed
   to you under the terms of the applicable Commercial License.

********************************************************************************
   Marvell GPL License Option

   If you received this File from Marvell, you may opt to use, redistribute and/or
   modify this File in accordance with the terms and conditions of the General
   Public License Version 2, June 1991 (the "GPL License"), a copy of which is
   available along with the File in the license.txt file or by writing to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 or
   on the worldwide web at http://www.gnu.org/licenses/gpl.txt.

   THE FILE IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE IMPLIED
   WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY
   DISCLAIMED.  The GPL License provides additional details about this warranty
   disclaimer.
********************************************************************************
   Marvell BSD License Option

   If you received this File from Marvell, you may opt to use, redistribute and/or
   modify this File under the following licensing terms.
   Redistribution and use in source and binary forms, with or without modification,
   are permitted provided that the following conditions are met:

*   Redistributions of source code must retain the above copyright notice,
            this list of conditions and the following disclaimer.

*   Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

*   Neither the name of Marvell nor the names of its contributors may be
        used to endorse or promote products derived from this software without
        specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
   ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
   ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*******************************************************************************/

#ifndef __INCmvCtrlEnvLibh
#define __INCmvCtrlEnvLibh

#include "mvSysHwConfig.h"
#include "mvCommon.h"
#include "mvTypes.h"
#include "mvOs.h"
#include "ctrlEnv/mvCtrlEnvSpec.h"
#include "ctrlEnv/mvCtrlEnvRegs.h"
#include "ctrlEnv/mvCtrlEnvAddrDec.h"


typedef enum _mvConfigTypeID {
	MV_CONFIG_MII,			/* MII board SLM 1362	*/
	MV_CONFIG_SLIC_TDM_DEVICE,	/* TDM board SLM 1360	*/
	MV_CONFIG_I2S_DEVICE,		/* I2S board SLM 1360	*/
	MV_CONFIG_SPDIF_DEVICE,		/* SPDIF board SLM 1360	*/
	MV_CONFIG_NOR,			/* NOR board SLM 1361	*/
	MV_CONFIG_NAND,			/* NAND board SLM 1361	*/
	MV_CONFIG_SDIO,			/* SDIO board SLM 1361	*/
	MV_CONFIG_GIGA,			/* GIGA board SLM	*/
	MV_CONFIG_SGMII,		/* SERDES module SGMII	*/
	MV_CONFIG_SERDES_PEX_LAN1,	/* SERDES module PEX	*/
	MV_CONFIG_SERDES_PEX_LAN2,	/* SERDES module PEX	*/
	MV_CONFIG_TYPE_MAX_MODULE,
	MV_CONFIG_NAND_ON_BOARD = MV_CONFIG_TYPE_MAX_MODULE,	/* ON board nand detect */
	MV_CONFIG_TYPE_MAX_OPTION,
} MV_CONFIG_TYPE_ID;


/* This enumerator describes the possible SMI control options */
typedef enum _mvSMIctrl {
	CPU_SMI_CTRL,
	SWITCH_SMI_CTRL,
} MV_SMI_CTRL;

/* typedefs */
typedef MV_STATUS (*MV_WIN_GET_FUNC_PTR)(MV_U32, MV_U32, MV_UNIT_WIN_INFO*);

/* This enumerator describes the possible HW cache coherency policies the
 * controllers supports.
 */
typedef enum _mvCachePolicy {
	NO_COHERENCY,   /* No HW cache coherency support                        */
	WT_COHERENCY,   /* HW cache coherency supported in Write Through policy */
	WB_COHERENCY    /* HW cache coherency supported in Write Back policy    */
} MV_CACHE_POLICY;

/* The swapping is referred to a 64-bit words (as this is the controller
 * internal data path width). This enumerator describes the possible
 * data swap types. Below is an example of the data 0x0011223344556677
 */
typedef enum _mvSwapType {
	MV_BYTE_SWAP,           /* Byte Swap                77 66 55 44 33 22 11 00 */
	MV_NO_SWAP,             /* No swapping              00 11 22 33 44 55 66 77 */
	MV_BYTE_WORD_SWAP,      /* Both byte and word swap  33 22 11 00 77 66 55 44 */
	MV_WORD_SWAP,           /* Word swap                44 55 66 77 00 11 22 33 */
	SWAP_TYPE_MAX           /* Delimiter for this enumerator                    */
} MV_SWAP_TYPE;

/*
 * Define the different Ethernet complex sources for the RGMIIA/B and
 * the FE/GE phy interfaces.
 */
typedef enum {
	MV_ETHCOMP_SW_GE_0_1_DEFAULT		=	BIT0,
	MV_ETHCOMP_SW_GE_0_1_SGMII_MODULE	=	BIT1,
	MV_ETHCOMP_SW_GE_0_MII_MODULE		=	BIT2,
} MV_ETH_COMPLEX_TOPOLOGY;

typedef enum {
	EPM_DEFAULT = 0x0,      /* RGMII */
	EPM_MAC0_MII = 0x01,
	EPM_MAC1_MII = 0x10,
	EPM_SW_PORT_5_MII = 0x100,
	EPM_SW_PORT_6_MII = 0x1000
} MV_ETH_PORT_MODE;

typedef enum {
	SERDES_UNIT_NA		= 0x0,
	SERDES_UNIT_PEX		= 0x10,
	SERDES_UNIT_SATA	= 0x20,
	SERDES_UNIT_GBE		= 0x30,
	SERDES_UNIT_USB_H	= 0x40,
	SERDES_UNIT_USB		= 0x50,
} MV_SERDES_UNIT_INDX;

typedef enum {
	PEX_BUS_DISABLED        = 0,
	PEX_BUS_MODE_X1         = 1,
	PEX_BUS_MODE_X4         = 2,
	PEX_BUS_MODE_X8         = 3
} MV_PEX_UNIT_CFG;
/*
	This enum should reflect the units numbers in register
	space which we will need when accessing the HW
*/

typedef enum {
	PEX0_IF,
	PEX1_IF,
	PEX2_IF,
	PEX3_IF,
	PEXIF_MAX
} MV_PEXIF_INDX;

/*
	This structure refrect registers:
	Serdes 0-6 selectors		0x183fc
*/

#define SERDES_CFG {	\
/* Lane 0 */ {SERDES_UNIT_NA,		SERDES_UNIT_PEX | PEX0_IF, SERDES_UNIT_SATA | 0,	SERDES_UNIT_GBE  | 0,\
	      SERDES_UNIT_NA,		SERDES_UNIT_NA,		    SERDES_UNIT_NA,		SERDES_UNIT_NA},     \
/* Lane 1 */ {SERDES_UNIT_NA,		SERDES_UNIT_PEX | PEX0_IF, SERDES_UNIT_NA,		SERDES_UNIT_SATA | 0,\
	      SERDES_UNIT_GBE | 0,	SERDES_UNIT_GBE | 1,	    SERDES_UNIT_NA,		SERDES_UNIT_NA},     \
/* Lane 2 */ {SERDES_UNIT_NA,		SERDES_UNIT_PEX | PEX1_IF, SERDES_UNIT_NA,		SERDES_UNIT_SATA | 1,\
	      SERDES_UNIT_GBE | 1,	SERDES_UNIT_NA,		    SERDES_UNIT_NA,		SERDES_UNIT_NA},     \
/* Lane 3 */ {SERDES_UNIT_NA,		SERDES_UNIT_PEX | PEX3_IF, SERDES_UNIT_NA,		SERDES_UNIT_SATA | 3,\
	      SERDES_UNIT_GBE | 2,	SERDES_UNIT_USB_H | 1,	    SERDES_UNIT_USB,		SERDES_UNIT_NA},     \
/* Lane 4 */ {SERDES_UNIT_NA,		SERDES_UNIT_PEX | PEX1_IF, SERDES_UNIT_SATA | 1,	SERDES_UNIT_GBE  | 1,\
	      SERDES_UNIT_USB_H | 0,	SERDES_UNIT_USB,	    SERDES_UNIT_NA,		SERDES_UNIT_NA},     \
/* Lane 5 */ {SERDES_UNIT_NA,		SERDES_UNIT_PEX | PEX2_IF, SERDES_UNIT_SATA | 2,	SERDES_UNIT_GBE  | 2,\
	      SERDES_UNIT_USB_H | 1,	SERDES_UNIT_USB,	    SERDES_UNIT_NA,		SERDES_UNIT_NA},     \
}



/* Termal Sensor Registers */
#define TSEN_STATE_REG						0xE4070
#define TSEN_STATE_OFFSET					31
#define TSEN_STATE_MASK						(0x1 << TSEN_STATE_OFFSET)

#define TSEN_CONF_REG						0xE4074
#define TSEN_CONF_OTF_CALIB_MASK				(0x1 << 8)

#define TSEN_STATUS_REG						0xE4078
#define TSEN_STATUS_TEMP_OUT_OFFSET				0
#define TSEN_STATUS_TEMP_OUT_MASK				(0x3FF << TSEN_STATUS_TEMP_OUT_OFFSET)


/* BIOS Modes related defines */
#define SAR_CPU_FAB_GET(cpu, fab)       (((cpu & 0x7) << 21) | ((fab & 0xF) << 24))

/* mcspLib.h API list */
MV_STATUS mvCtrlCpuDdrL2FreqGet(MV_FREQ_MODE *freqMode);
MV_U32 mvCtrlbootSrcGet(void);
MV_U32 mvCtrlSysConfigGet(MV_CONFIG_TYPE_ID configField);
MV_U32 mvCtrlGetCpuNum(MV_VOID);
MV_U32 mvCtrlGetQuadNum(MV_VOID);
MV_STATUS mvCtrlUpdatePexId(MV_VOID);
MV_BOOL mvCtrlIsEepromEnabled(MV_VOID);
MV_STATUS mvCtrlEepromEnable(MV_BOOL enable);
MV_STATUS mvCtrlBoardConfigGet(MV_U8 *tempVal);
MV_U32 mvCtrlSocUnitInfoNumGet(MV_UNIT_ID unit);
MV_U32 mvCtrlSocUnitInfoNumSet(MV_UNIT_ID unit, MV_U32 maxValue);
MV_STATUS mvCtrlEnvInit(MV_VOID);
MV_U32    mvCtrlMppRegGet(MV_U32 mppGroup);
MV_U32 mvCtrlGetJuncTemp(MV_VOID);
void mvCtrlNandClkSet(int nClock);

#if defined(MV_INCLUDE_PEX)
MV_U32 mvCtrlPexMaxIfGet(MV_VOID);
MV_U32 mvCtrlPexMaxUnitGet(MV_VOID);
#else
#define mvCtrlPciMaxIfGet()             1
#endif
MV_U32 mvCtrlPexActiveUnitNumGet(MV_VOID);

#if defined(MV_INCLUDE_PCI)
#define mvCtrlPciIfMaxIfGet()           3
#else
#define mvCtrlPciIfMaxIfGet()           3
#endif

MV_U32 mvCtrlEthMaxPortGet(MV_VOID);
MV_U8 mvCtrlEthMaxCPUsGet(MV_VOID);

MV_U32 mvCtrlSataMaxPortGet(MV_VOID);
#if defined(MV_INCLUDE_XOR)
MV_U32 mvCtrlXorMaxChanGet(MV_VOID);
MV_U32 mvCtrlXorMaxUnitGet(MV_VOID);
#endif
#if defined(MV_INCLUDE_USB)
MV_U32 mvCtrlUsbMaxGet(MV_VOID);
MV_U32 mvCtrlUsb3MaxGet(MV_VOID);
#endif
#if defined(MV_INCLUDE_SDIO)
MV_U32 mvCtrlSdioSupport(MV_VOID);
#endif
MV_U32 mvCtrlTdmSupport(MV_VOID);
MV_U32 mvCtrlTdmMaxGet(MV_VOID);
MV_TDM_UNIT_TYPE mvCtrlTdmUnitTypeGet(MV_VOID);
MV_U32 mvCtrlTdmUnitIrqGet(MV_VOID);
MV_U32 mvCtrlDevFamilyIdGet(MV_U16 ctrlModel);
MV_U16 mvCtrlModelGet(MV_VOID);
MV_U8 mvCtrlRevGet(MV_VOID);
MV_STATUS mvCtrlNameGet(char *pNameBuff);
MV_U32 mvCtrlModelRevGet(MV_VOID);
MV_STATUS mvCtrlModelRevNameGet(char *pNameBuff);
MV_VOID mvCtrlAddrDecShow(MV_VOID);
const MV_8 *mvCtrlTargetNameGet(MV_TARGET target);
MV_U32    ctrlSizeToReg(MV_U32 size, MV_U32 alignment);
MV_U32    ctrlRegToSize(MV_U32 regSize, MV_U32 alignment);
MV_U32    ctrlSizeRegRoundUp(MV_U32 size, MV_U32 alignment);
MV_U32 mvCtrlSysRstLengthCounterGet(MV_VOID);
MV_STATUS ctrlWinOverlapTest(MV_ADDR_WIN *pAddrWin1, MV_ADDR_WIN *pAddrWin2);
MV_STATUS ctrlWinWithinWinTest(MV_ADDR_WIN *pAddrWin1, MV_ADDR_WIN *pAddrWin2);
MV_VOID mvCtrlSmiMasterSet(MV_SMI_CTRL smiCtrl);
MV_VOID mvCtrlPwrClckSet(MV_UNIT_ID unitId, MV_U32 index, MV_BOOL enable);
MV_BOOL mvCtrlPwrClckGet(MV_UNIT_ID unitId, MV_U32 index);
MV_BOOL mvCtrlIsBootFromNOR(MV_VOID);
MV_BOOL mvCtrlIsBootFromSPI(MV_VOID);
MV_BOOL mvCtrlIsBootFromNAND(MV_VOID);
MV_U32 mvCtrlDDRBudWidth(MV_VOID);
MV_BOOL mvCtrlDDRThruXbar(MV_VOID);
MV_BOOL mvCtrlDDRECC(MV_VOID);

#endif /* __INCmvCtrlEnvLibh */
