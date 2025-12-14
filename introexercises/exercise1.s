.psx
.create "exercise1.bin", 0x80010000

.org 0x80010000

Main:
    li $t0, 0x01
    li $t1, 0xF0
    li $t2, 0xF1
End:
.close