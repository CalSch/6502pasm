; this code isn't tested to be functional or good, just a syntax demo

.org #$0800
    jmp main

mul: ; Multiply the values at X and Y (zeropage)
    lda #$0
mul_loop:
    cpy #$00
    beq mul_end
    dey
    adc $00,X
    jmp mul_loop
mul_end:
    rts
main:
    ldx #$01 ; immediate addressing
    LDY #$02 ; capital mnemonic
    lda #$05
    sta $00,X ; zeropage X
    lda #$03
    sta $00,Y
    jsr mul ; subroutine

