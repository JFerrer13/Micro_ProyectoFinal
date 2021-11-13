        AREA |.text|, CODE, READONLY, ALIGN=2
        THUMB
        REQUIRE8
        PRESERVE8

        EXPORT registers_to_array
		
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

	end
	