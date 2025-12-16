.psx
.create "HELLOGPU.bin", 0x80010000

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
    li $t1, 0x08000009
    sw $t1, GP1($t0)

    ; Display Area Start (X=0, Y=0)
    li $t1, 0x05000000
    sw $t1, GP1($t0)

    ; Set Horizonal Range
    li $t1, 0x06C60260
    sw $t1, GP1($t0)

    ; Set Vertical Range
    li $t1, 0x07042818
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

    ;;; Clear Screen
    li $t1, 0x0280045A
    sw $t1, GP0($t0)
    li $t1, 0x00000000
    sw $t1, GP0($t0)
    li $t1, 0x00EF013F
    sw $t1, GP0($t0)

    ;;; Draw Flat Shaded Quad
    li $t1, 0x2803DE33
    sw $t1, GP0($t0)
    li $t1, 0x00A00050
    sw $t1, GP0($t0)
    li $t1, 0x00A000F0
    sw $t1, GP0($t0)
    li $t1, 0x00F00050
    sw $t1, GP0($t0)
    li $t1, 0x00F000F0
    sw $t1, GP0($t0)

    ;;; Draw Flat Shaded Triangle
    lui $a0, IO_BASE_ADDR
    li $s0, 0xFFFF00
    li $s1, 200
    li $s2, 40
    li $s3, 288
    li $s4, 56
    li $s5, 224
    li $s6, 200
    jal DrawFlatShadedTriangle
    nop


LoopForever:
    j LoopForever
    nop

;;;;;;;;;;
;; Subroutine to draw flat shaded triangle
;; Args:
;; $a0 = IO_BASE_ADDR
;; $s0 = Color
;; $s1 = x1
;; $s2 = y1
;; $s3 = x2
;; $s4 = y2
;; $s5 = x3
;; $s6 = y3
;;;;;;;;;;
DrawFlatShadedTriangle:
    lui $t0, 0x2000
    or $t1, $t0, $s0
    sw $t1, GP0($a0)

    sll $s2, $s2, 16
    andi $s1, $s1, 0xFFFF
    or $t1, $s1, $s2
    sw $t1, GP0($a0)

    sll $s4, $s4, 16
    andi $s3, $s3, 0xFFFF
    or $t1, $s3, $s4
    sw $t1, GP0($a0)

    sll $s6, $s6, 16
    andi $s5, $s5, 0xFFFF
    or $t1, $s5, $s6
    sw $t1, GP0($a0)

    jr $ra
    nop

End:

.close