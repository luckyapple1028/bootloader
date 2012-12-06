

.text
.global _start

_start:
	/* ����ջ */
	ldr sp, =0xD0030000
	/* ��ʼ��ʱ�� */
	bl clock_init
	/* ��ʼ��DDR */
	bl mem_ctrl_asm_init

	/* �ض�λ */
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

	/* ִ��main����ʹ��λ�����������ת */
	ldr sp, =0x33e00000	
	ldr lr, =halt
	ldr pc, =mymain

halt:
	b halt

	