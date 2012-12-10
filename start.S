

.text
.global _start


_start:
	b reset      /* CPU复位 */

reset:
	/* 设置栈 */
	ldr sp, =0xD0030000
	/* 初始化时钟 */
	bl clock_init
	/* 初始化DDR */
	bl mem_ctrl_asm_init

	/* 重定位 */
	ldr r0, =0xD0020000
	ldr r1, =0x20000000	@ copy to SDRAM
	ldr r2, =0x4000		@ size = 16K

move_loop:
	ldr r3, [r0]
	str r3, [r1]
	add r0, r0, #4
	add r1, r1, #4
	sub r2, r2, #4
	cmp r2, #0
	bne move_loop
	/* here we use ldr instead of b to jump to SDRAM */
	/* in addition, we should change -T0x20000010 for using SDRAM */

	/*清bss段*/
	bl clear_bss

	/* 中断初始化 */
	mrs r0, cpsr
	bic r0,r0,#0x80  /* 清cpsr的I位 */
	msr cpsr, r0
	
	/* 执行main程序，使用位置相关码来跳转 */
	ldr sp, =0x33e00000
	ldr lr, =halt
	ldr pc, =mymain

halt:
	b halt

	
