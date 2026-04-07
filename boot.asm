[org 0x7c00]

mov bx, 0x1000

mov ah, 0x02
mov al, 10
mov ch, 0
mov dh, 0
mov cl, 2
int 0x13

cli
lgdt [gdt_descriptor]

mov eax, cr0
or eax, 1
mov cr0, eax

jmp CODE_SEG:protected_mode

[bits 32]
protected_mode:

mov ax, DATA_SEG
mov ds, ax
mov ss, ax
mov es, ax
mov fs, ax
mov gs, ax

jmp 0x1000

; -----------------
; GDT
; -----------------

gdt_start:

gdt_null: dq 0x0

gdt_code:
dw 0xffff
dw 0x0000
db 0x00
db 10011010b
db 11001111b
db 0x00

gdt_data:
dw 0xffff
dw 0x0000
db 0x00
db 10010010b
db 11001111b
db 0x00

gdt_end:

gdt_descriptor:
dw gdt_end - gdt_start - 1
dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

times 510-($-$$) db 0
dw 0xaa55
