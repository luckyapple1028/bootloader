	.globl eint16_31_irq
	.globl eint_rtc_irq

eint16_31_irq:

	/* 保存现场 */
	ldr sp, =0x35000000
	sub lr, lr, #4			  /* 执行指令前会先判断是否有中断，所以要保存的是当前指令而不是下一条指令 */
	stmdb sp!, {r0-r12, lr}   /* lr就是中断前系一条要执行的指令地址 */

	bl do_eint16_31_irq
	/* 恢复现场 */
	ldmia sp!, {r0-r12, pc}^  /* ^表示把spsr恢复到cpsr */

eint_rtc_irq:

	/* 保存现场 */
	ldr sp, =0x35000000
	sub lr, lr, #4			  /* 执行指令前会先判断是否有中断，所以要保存的是当前指令而不是下一条指令 */
	stmdb sp!, {r0-r12, lr}   /* lr就是中断前系一条要执行的指令地址 */
	
	bl do_eint_rtc_irq
	/* 恢复现场 */
	ldmia sp!, {r0-r12, pc}^  /* ^表示把spsr恢复到cpsr */

	

