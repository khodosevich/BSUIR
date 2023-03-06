data segment
    writingError db 10, 13, "Write error!$"
    readingError db 10, 13, "Read error!$"
    output db "Your symbol: $"
    dataForSending db ?
    dataForReading db ?
    enterSymbol db "Enter the symbol: $"  
data ends

code segment
    
    
    
    Exit proc
        mov ax, 4C00h
        int 21h
        ret 
    Exit endp
    
    start:
        mov ax, @data
        mov ds, ax       
        
        mov al, 80h      ; initialize
        mov dx, 3FBh
        out dx, al
        
        mov dx, 3F8h
        mov al, 00h
        out dx, al
        mov al, 0Ch
        mov dx, 3F9h
        out dx, al
        
        mov dx, 3FCh
        mov al, 00001011b
        out dx ,al
        
        mov dx, 3F9h
        mov al, 0
        out dx, al
        
        xor al, al ; Is Writed in com1  
        mov dx, 3FDh
        in al, dx
        test al, 10h
        jnz NoWrite
        
        
        mov ah, 9h                 ;read symbol
        mov dx, offset enterSymbol
        int 21h
        
        xor ax, ax
        
        MOV AH, 01H      
        INT 21H
        mov dataForSending, al
        
        mov ah, 02h
        mov dl, 0ah
        int 21h
        
        mov ah, 02h
        mov dl, 0dh
        int 21h

        
        mov dx, 3F8h           ;send data
        mov al, dataForSending
        out dx, al 
        
        mov al, 02h 
        
        xor al, al    ;is readed from com2
        mov dx, 3FDh
        in al, dx
        test al, 10b
        jnz NoRead
         
        
        mov dx, 3F8h     ; read data
        in al, dx
        mov dataForReading, al   
        
        mov dx, offset output
        mov ah, 09h
        int 21h    
        
        mov ah, 02h
        mov dl, dataForReading
        int 21h   
        
        call Exit
    NoWrite:  
        mov ah, 09h
        mov dx, offset writingError
        int 21h 
        call Exit
    NoRead:
        mov ah, 09h
        mov dx, offset readingError
        int 21h
        call Exit
        
        code ends    

end start