; this code isn't tested to be functional or good, just a syntax demo

.macro cool_macro #$05

.org $0010
    jmp main

mul: ; Multiply the values at X and Y (zeropage)
    lda #$00
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
    lda %cool_macro ; expands #$05
    sta $00,X ; zeropage X
    lda #$03
    jsr mul ; subroutine

