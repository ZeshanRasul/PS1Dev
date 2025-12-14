.psx
.create "hellogpu.bin", 0x80010000

.org 0x80010000

;;; IO Port
IO_BASE_ADDR equ 0x1F80

;;; GPU Registers
GP0 equ 0x1810
GP1 equ 0x1814

Main:
    lui $t0, IO_BASE_ADDR 

    ;;; Display Setup
    
    ; Reset GPU
    li $t1, 0x00000000  ;Command to reset GPU
    sw $t1, GP1($t0)    ;Write packet containing command to GP1

    ; Enable Display
    li $t1, 0x03000000
    sw $t1, GP1($t0)

    ; Display Mode
    li $t1, 0x08000101
    sw $t1, GP1($t0)

    ; Set Horizonal Range
    li $t1, 0x06C60260
    sw $t1, GP1($t0)

    ; Set Vertical Range
    li $t1, 0x07042018
    sw $t1, GP1($t0)

    ;;; Setup VRAM Access
    
    ; Draw Mode Settings
    li $t1, 0xE1000400
    sw $t1, GP0($t0)

    ; Drawing Area Top Left
    li $t1, 0xE3000000
    sw $t1, GP0($t0)

    ; Drawing Area Bottom Right
    li $t1, 0xE403BD3F
    sw $t1, GP0($t0)

    ; Drawing Offset
    li $t1, 0xE5000000
    sw $t1, GP0($t0)

End:

.close