;-----------------------------------------------------------------------		
;
; XEX2COLD restarter for SWITCHABLE XEGS CARTRIDGE
; (c) 2022 GienekP
;
;-----------------------------------------------------------------------

		ORG $0600

		jsr $C2C8
		lda #$00
		sta $d500
		jmp $C2C8

;-----------------------------------------------------------------------		