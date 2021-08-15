global outb
global inb

; outb - send a byte to I/O port
; stack: [esp + 8] the data byte
;        [eso + 4] the I/O port
;        [eso    ] return address
outb:
    mov al, [esp + 8]   ; move data to be sent into al register 
    mov dx, [esp + 4]   ; move addr of I/O port to dx 
    out dx, al          ; send data to I/O port
    ret

; inb - returns a byte from the given I/O port
; stack: [esp + 4] The address of the I/O port
;        [esp    ] The return addr
inb:
    mov dx, [esp + 4]   ; move addr of I/O port to dx register
    in al, dx           ; read byte from I/O port and store in al register
    ret                 ; return read byte