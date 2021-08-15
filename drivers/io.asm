global outb     ; Make label public

; outb - send a byte to I/O port
; stack: [esp + 8] the data byte
;        [eso + 4] the I/O port
;        [eso    ] return address
outb:
    mov al, [esp + 8]   ; move data to be sent into al register 
    mov dx, [esp + 4]   ; move addr of I/O port to dx 
    out dx, al          ; send data to I/O port
    ret