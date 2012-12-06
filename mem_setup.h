/*
 * SDRAM Controller
 */
#define APB_DMC_0_BASE			0xF0000000
#define APB_DMC_1_BASE			0xF1400000
#define ASYNC_MSYS_DMC0_BASE		0xF1E00000

#define ELFIN_GPIO_BASE			0xE0200000

#define DMC0_MEMCONTROL		0x00202400	// MemControl	BL=4, 1Chip, DDR2 Type, dynamic self refresh, force precharge, dynamic power down off
#define DMC0_MEMCONFIG_0	0x20E00323	// MemConfig0	256MB config, 8 banks,Mapping Method[12:15]0:linear, 1:linterleaved, 2:Mixed
#define DMC0_MEMCONFIG_1	0x00E00323	// MemConfig1

#define DMC0_TIMINGA_REF        0x00000618      // TimingAref   7.8us*133MHz=1038(0x40E), 100MHz=780(0x30C), 20MHz=156(0x9C), 10MHz=78(0x4E)
#define DMC0_TIMING_ROW         0x2B34438A      // TimingRow    for @200MHz
#define DMC0_TIMING_DATA        0x24240000      // TimingData   CL=3
#define DMC0_TIMING_PWR         0x0BDC0343      // TimingPower

#define	DMC1_MEMCONTROL		0x00202400	// MemControl	BL=4, 2 chip, DDR2 type, dynamic self refresh, force precharge, dynamic power down off
#define DMC1_MEMCONFIG_0	0x40F00313	// MemConfig0	512MB config, 8 banks,Mapping Method[12:15]0:linear, 1:linterleaved, 2:Mixed
#define DMC1_MEMCONFIG_1	0x00F00313	// MemConfig1

#define DMC1_TIMINGA_REF        0x00000618      // TimingAref   7.8us*133MHz=1038(0x40E), 100MHz=780(0x30C), 20MHz=156(0x9C), 10MHz=78(0x4E)
#define DMC1_TIMING_ROW         0x2B34438A      // TimingRow    for @200MHz
#define DMC1_TIMING_DATA        0x24240000      // TimingData   CL=3
#define DMC1_TIMING_PWR         0x0BDC0343      // TimingPower


#define MP1_0DRV_SR_OFFSET 		0x3CC
#define MP1_1DRV_SR_OFFSET 		0x3EC
#define MP1_2DRV_SR_OFFSET 		0x40C
#define MP1_3DRV_SR_OFFSET 		0x42C
#define MP1_4DRV_SR_OFFSET 		0x44C
#define MP1_5DRV_SR_OFFSET 		0x46C
#define MP1_6DRV_SR_OFFSET 		0x48C
#define MP1_7DRV_SR_OFFSET 		0x4AC
#define MP1_8DRV_SR_OFFSET 		0x4CC

#define MP2_0DRV_SR_OFFSET 		0x4EC
#define MP2_1DRV_SR_OFFSET 		0x50C
#define MP2_2DRV_SR_OFFSET 		0x52C
#define MP2_3DRV_SR_OFFSET 		0x54C
#define MP2_4DRV_SR_OFFSET 		0x56C
#define MP2_5DRV_SR_OFFSET 		0x58C
#define MP2_6DRV_SR_OFFSET 		0x5AC
#define MP2_7DRV_SR_OFFSET 		0x5CC
#define MP2_8DRV_SR_OFFSET 		0x5EC

#define DMC_CONCONTROL 			0x00
#define DMC_MEMCONTROL 			0x04
#define DMC_MEMCONFIG0 			0x08
#define DMC_MEMCONFIG1 			0x0C
#define DMC_DIRECTCMD 			0x10
#define DMC_PRECHCONFIG 		0x14
#define DMC_PHYCONTROL0 		0x18
#define DMC_PHYCONTROL1 		0x1C
#define DMC_RESERVED 			0x20
#define DMC_PWRDNCONFIG 		0x28
#define DMC_TIMINGAREF 			0x30
#define DMC_TIMINGROW 			0x34
#define DMC_TIMINGDATA 			0x38
#define DMC_TIMINGPOWER 		0x3C
#define DMC_PHYSTATUS 			0x40
#define DMC_CHIP0STATUS 		0x48
#define DMC_CHIP1STATUS 		0x4C
#define DMC_AREFSTATUS 			0x50
#define DMC_MRSTATUS 			0x54
#define DMC_PHYTEST0 			0x58
#define DMC_PHYTEST1 			0x5C
#define DMC_QOSCONTROL0 		0x60
#define DMC_QOSCONFIG0 			0x64
#define DMC_QOSCONTROL1 		0x68
#define DMC_QOSCONFIG1 			0x6C
#define DMC_QOSCONTROL2 		0x70
#define DMC_QOSCONFIG2 			0x74
#define DMC_QOSCONTROL3 		0x78
#define DMC_QOSCONFIG3 			0x7C
#define DMC_QOSCONTROL4 		0x80
#define DMC_QOSCONFIG4 			0x84
#define DMC_QOSCONTROL5 		0x88
#define DMC_QOSCONFIG5 			0x8C
#define DMC_QOSCONTROL6 		0x90
#define DMC_QOSCONFIG6 			0x94
#define DMC_QOSCONTROL7 		0x98
#define DMC_QOSCONFIG7 			0x9C
#define DMC_QOSCONTROL8 		0xA0
#define DMC_QOSCONFIG8 			0xA4
#define DMC_QOSCONTROL9 		0xA8
#define DMC_QOSCONFIG9 			0xAC
#define DMC_QOSCONTROL10 		0xB0
#define DMC_QOSCONFIG10 		0xB4
#define DMC_QOSCONTROL11 		0xB8
#define DMC_QOSCONFIG11 		0xBC
#define DMC_QOSCONTROL12 		0xC0
#define DMC_QOSCONFIG12 		0xC4
#define DMC_QOSCONTROL13 		0xC8
#define DMC_QOSCONFIG13 		0xCC
#define DMC_QOSCONTROL14 		0xD0
#define DMC_QOSCONFIG14 		0xD4
#define DMC_QOSCONTROL15 		0xD8
#define DMC_QOSCONFIG15 		0xDC

