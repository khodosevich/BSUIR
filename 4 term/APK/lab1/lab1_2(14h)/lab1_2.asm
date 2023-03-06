.model small
.stack 100h

.data

Error_Write db "Write error!",0Dh,0Ah,'$'
Error_Read db "Read error!",0Dh,0Ah,'$'
InputStroka db "Enter the symbol: ",0Dh,0Ah,'$'
OutputStroka db "Your symbol: $"
           
.code

Exit proc
    mov ax,4C00h
    int 21h
    ret
Exit endp

start:
    mov ax, data
    mov ds, ax
    
    xor ax,ax ; initialization Com1
    mov al,10100011b;2400 - speed, without paritet, 8 bit, stop bit - 1
    mov dx,0 
    int 14h 
    
    xor ax, ax
    
    mov ah, 09h
    mov dx, offset InputStroka
    int 21h
    
    xor ax, ax
    
    MOV AH, 01H      
    INT 21H
     
    mov ah,1
    mov dx,0
    int 14h
    test al,80h
    jnz NoWrite
    
    mov al,'e'   ; Is read Com2
    mov ah,2
    mov dx,1
    int 14h
    test al,80h
    jnz NoRead
        
    mov ah,02h     ;Output
    mov dl,al
    int 21h
   
   
   call Exit
    
NoWrite: 
   mov ah,9
   mov dx,offset Error_Write
   add dx,2
   int 21h
   call Exit
    
NoRead:
   mov ah,9
   mov dx,offset Error_Read
   add dx,2
   int 21h
   call Exit
   

    
end start