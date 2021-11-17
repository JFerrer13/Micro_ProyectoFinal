        AREA |.text|, CODE, READONLY, ALIGN=2
        THUMB
        REQUIRE8
        PRESERVE8

        EXPORT registers_to_array
		EXPORT cambiar_r1
		EXPORT cambiar_r2
		EXPORT cambiar_r3
		EXPORT cambiar_r4
		EXPORT cambiar_r5
		EXPORT cambiar_r6
		EXPORT cambiar_r7		
		EXPORT cambiar_r8
		EXPORT cambiar_r9
		EXPORT cambiar_r10
		EXPORT cambiar_r11
		EXPORT cambiar_r12	
		EXPORT desplegar_memoria
		EXPORT cambiar_byte
		EXPORT cambiar_half
		EXPORT cambiar_word	
		EXPORT ejecutar
		EXPORT ir_direccion
		EXPORT reset	
			
registers_to_array
	push {lr}
	
	str r0,  [r0,#0x0]
	str r1,  [r0,#0x4]
	str r2,  [r0,#0x8]
	str r3,  [r0,#0xC]
	str r4,  [r0,#0x10]
	str r5,  [r0,#0x14]
	str r6,  [r0,#0x18]
	str r7,  [r0,#0x1C]
	str r8,  [r0,#0x20]
	str r9,  [r0,#0x24]
	str r10, [r0,#0x28]
	str r11, [r0,#0x2C]
	str r12, [r0,#0x30]
	str r13, [r0,#0x34]
	str r14, [r0,#0x38]
	pop {pc}

cambiar_r1
	push {lr}
	movs r1, r0
	pop {pc}
cambiar_r2
	push {lr}
	movs r2, r0
	pop {pc}
cambiar_r3
	push {lr}
	movs r3, r0
	pop {pc}
cambiar_r4
	push {lr}
	movs r4, r0
	pop {pc}
cambiar_r5
	push {lr}
	movs r5, r0
	pop {pc}
cambiar_r6
	push {lr}
	movs r6, r0
	pop {pc}
cambiar_r7
	push {lr}
	movs r7, r0
	pop {pc}
cambiar_r8
	push {lr}
	movs r8, r0
	pop {pc}
cambiar_r9
	push {lr}
	movs r9, r0
	pop {pc}
cambiar_r10
	push {lr}
	movs r10, r0
	pop {pc}
cambiar_r11
	push {lr}
	movs r11, r0
	pop {pc}
cambiar_r12
	push {lr}
	movs r12, r0
	pop {pc}

desplegar_memoria
	push {lr}	
	
	ldr r2, [r1,#0x0]
	str r2, [r0,#0x0]
	
	pop {pc}

cambiar_byte	
	push {lr}
	strb r1, [r0, #0x0]
	pop {pc}

cambiar_half
	push {lr}
	strh r1, [r0, #0x0]
	pop {pc}

cambiar_word
	push {lr}
	str r1, [r0, #0x0]	
	pop {pc}

ejecutar
  bx r0

ir_direccion
  blx r0

reset	
	
	ldr r1, [r0, #0x0]
	bx r1
	
end