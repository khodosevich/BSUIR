    .model small
    .stack 100h 
    .code    

hex_to_str proc
    pusha   
    mov di,18h
    mov cx,2h  
    mov bx,0Ah 
    cmp ax,5Ah
    jae win_
    jb translate_loop
win_:         
    inc win       

translate_loop:
    xor dx,dx              
    div bx 
    push dx
    xor dx,dx
    cmp ax,0h
    je _end 
    loop translate_loop   
         
_end:                    
    mov cx,2h 
        
write_number:
    pop dx  
    add dx,30h              
    mov es:[di],dl 
    inc di 
    mov es:[di],00001111b 
    inc di
    loop write_number   
        
_end_:        
    mov es:[di],'%'
    inc di
    mov es:[di],00001111b    
    popa
    ret  
hex_to_str endp 

draw proc
    pusha 
    mov di,208h 
    mov bx,0h 
    
draw_cycle: 
    lea si,map[bx] 
    mov cx,50h 
    repe movsb 
    cmp bx,5F0h 
    je end_draw             
    add di,50h
    add bx,50h
    jmp draw_cycle     
    
end_draw:    
    popa           
    ret
draw endp

enemy_move proc
    pusha        
    mov bx,enemy_bx  
    cmp left_down,1h
    je move_left_down    
    cmp right_down,1h
    je move_right_down 
    cmp left_up,1h
    je move_left_up 
    cmp right_up,1h
    je move_right_up 

move_left_down:
    mov left_down,1h       
    mov right_down,0h 
    mov left_up,0h 
    mov right_up,0h 
    cmp map[bx+4Eh],'2'
    je game_over_     
    cmp map[bx+4Eh],'0'
    je game_over_       
    cmp map[bx+4Eh],'1'
    je move_left_up 
    
move_left_down_next:
    mov map[bx],'3'
    inc bx
    mov map[bx],00000000b      
    dec bx
    mov di,enemy_di
    lea si,map[bx]
    mov cx,2h
    repe movsb               
    add enemy_bx,4Eh    
    add enemy_di,09Eh
    mov di,enemy_di        
    mov bx,enemy_bx 
    mov map[bx],'4'
    inc bx
    mov map[bx],11111111b          
    dec bx
    mov di,enemy_di
    lea si,map[bx]
    mov cx,2h
    repe movsb    
    jmp break 

move_right_down: 
    mov right_down,1h
    mov left_down,0h   
    mov left_up,0h
    mov right_up,0h    
    cmp map[bx+52h],'2'
    je game_over_ 
    cmp map[bx+52h],'0'
    je game_over_          
    cmp map[bx+52h],'1'
    je move_left_down  
    
move_right_down_next:
    mov map[bx],'3'
    inc bx
    mov map[bx],00000000b      
    dec bx
    mov di,enemy_di
    lea si,map[bx]
    mov cx,2h
    repe movsb               
    add enemy_bx,52h    
    add enemy_di,0A2h
    mov di,enemy_di        
    mov bx,enemy_bx 
    mov map[bx],'4'
    inc bx
    mov map[bx],11111111b          
    dec bx
    lea si,map[bx]
    mov cx,2h
    repe movsb    
    jmp break     
    
move_left_up: 
    mov left_up,1h
    mov left_down,0h  
    mov right_down,0h
    mov right_up,0h      
    cmp map[bx-52h],'2'
    je game_over_
    cmp map[bx-52h],'0'
    je game_over_            
    cmp map[bx-52h],'1'
    je move_right_up    
    
move_left_up_next:
    mov map[bx],'3'
    inc bx
    mov map[bx],00000000b      
    dec bx
    mov di,enemy_di
    lea si,map[bx]
    mov cx,2h
    repe movsb               
    sub enemy_bx,52h    
    sub enemy_di,0A2h
    mov di,enemy_di        
    mov bx,enemy_bx 
    mov map[bx],'4'
    inc bx
    mov map[bx],11111111b          
    dec bx
    lea si,map[bx]
    mov cx,2h
    repe movsb    
    jmp break 
        
move_right_up:
    mov right_up,1h
    mov left_down,0h   
    mov right_down,0h
    mov left_up,0h 
    cmp map[bx-4Eh],'0'
    je game_over_      
    cmp map[bx-4Eh],'2'
    je game_over_             
    cmp map[bx-4Eh],'1'
    je move_right_down  
    
move_right_up_next:
    mov map[bx],'3'
    inc bx
    mov map[bx],00000000b      
    dec bx
    mov di,enemy_di
    lea si,map[bx]
    mov cx,2h
    repe movsb               
    sub enemy_bx,4Eh    
    sub enemy_di,9Eh
    mov di,enemy_di        
    mov bx,enemy_bx 
    mov map[bx],'4'
    inc bx
    mov map[bx],11111111b          
    dec bx
    lea si,map[bx]
    mov cx,2h
    repe movsb    
    jmp break 
    
game_over_:
    inc over 
    
break:   
    popa
    ret        
enemy_move endp    
  
move proc
    pusha  
    mov di,208h
    mov bx,0h  
    mov dh,3h
    mov dl,14h  
       
move_cycle:    
    cmp win,0h
    ja end_move
    call enemy_move
    cmp over,1h
    je end_move  
    push ax   
    mov ax,0100h     
    int 16h  
    cmp ah,1h
    je old_direction 
    jne new_direction  
    
old_direction:
    pop ax 
    jmp continue    
    
new_direction:   
    pop cx
    xor cx,cx 

continue:
    push ax
    mov ah,0Ch
    int 21h   
    pop ax 
    cmp ah,4Bh
    je left  
    cmp ah,4Dh
    je right
    cmp ah,48h
    je up
    cmp ah,50h
    je down
    jmp move_cycle

left:        
    cmp dl,14h
    je move_cycle     
    sub bx,50h   
    cmp map[bx],'1'
    je left_stay_on_purple 
    jne skip_left          
    
left_stay_on_purple:
    add bx,0A0h    
    cmp map[bx],'1'
    je left_sub_52h 
    
left_sub_52h:
    sub bx,52h
    jmp left_is_purple   
    
skip_left:      
    add bx,4Eh
    cmp map[bx],'1'
    je left_is_purple 
    cmp map[bx],'2'
    je end_move
    cmp map[bx],'3'  
    je left_is_black 
    cmp map[bx],'4'
    je end_move     
    
left_is_purple:
    cmp map[bx+4h],'2'
    je left_is_black
    add bx,2h
    mov map[bx],'1'
    inc bx
    mov map[bx],11011101b
    inc bx    
    jmp continue_left 

left_is_black: 

;    cmp map[bx],'1'
;    je left_set_fill_flag 
;    jne skip_left_   
;left_set_fill_flag:
;    mov fill_flag,1h
;skip_left_: 
 
    add bx,2h     
    cmp number,0h
    je left_set_start
    jne left_start_is_setted   
    
left_set_start:
    mov start_x,dl
    mov start_y,dh  
    
left_start_is_setted:    
    push bx
    add number,2h    
    mov map[bx],'2'
    inc bx
    mov map[bx],10011001b
    inc bx     
    jmp continue_left 
 
continue_left:   
    sub bx,4h 
    mov map[bx],'0'
    inc bx
    mov map[bx],10101010b
    inc bx       
    sub bx,2h
    lea si,map[bx]
    mov cx,4h     
    sub di,2h
    repe movsb 
    sub di,4h 
    dec dl        
    jmp move_cycle

right:   
    cmp dl,3Bh
    je move_cycle     
    sub bx,50h   
    cmp map[bx],'1'
    je right_stay_on_purple 
    jne skip_right      
    
right_stay_on_purple:
    add bx,0A0h    
    cmp map[bx],'1'
    je right_sub_4Eh  
    
right_sub_4Eh:
    sub bx,4Eh
    jmp right_is_purple  
     
skip_right:      
    add bx,52h 
    cmp map[bx],'1'
    je right_is_purple 
    cmp map[bx],'2'
    je end_move
    cmp map[bx],'3'  
    je right_is_black 
    cmp map[bx],'4'
    je end_move      
          
right_is_purple:       
    cmp map[bx-6h],'2'
    je right_is_black
    sub bx,2h
    mov map[bx],'1'
    inc bx
    mov map[bx],11011101b
    inc bx    
    jmp continue_right 

right_is_black: 

;    cmp map[bx],'1'
;    je right_set_fill_flag 
;    jne skip_right_   
;right_set_fill_flag:
;    mov fill_flag,1h
;skip_right_: 
 
    sub bx,2h       
    cmp number,0h
    je right_set_start
    jne right_start_is_setted 
    
right_set_start:
    mov start_x,dl
    mov start_y,dh       
    
right_start_is_setted:    
    push bx
    add number,2h    
    mov map[bx],'2'
    inc bx
    mov map[bx],10011001b
    inc bx     
    jmp continue_right 
    
continue_right:    
    mov map[bx],'0'
    inc bx
    mov map[bx],10101010b
    inc bx       
    sub bx,4h
    lea si,map[bx]
    mov cx,4h
    repe movsb 
    sub di,2h 
    add bx,2h
    inc dl    
    jmp move_cycle

up:   
    cmp dh,3h
    je move_cycle    
    sub bx,2h   
    cmp map[bx],'1'
    je up_stay_on_purple 
    jne skip_up   
    
up_stay_on_purple:
    add bx,4h    
    cmp map[bx],'1'
    je up_sub_52h 
    
up_sub_52h:
    sub bx,52h
    jmp up_is_purple    
        
skip_up:              
    sub bx,4Eh
    cmp map[bx],'1'
    je up_is_purple 
    cmp map[bx],'2'
    je end_move
    cmp map[bx],'3'  
    je up_is_black 
    cmp map[bx],'4'
    je end_move 
           
up_is_purple:  
    cmp map[bx+0A0h],'2'
    je up_is_black     
    add bx,50h
    mov map[bx],'1'
    inc bx
    mov map[bx],11011101b
    inc bx             
    jmp continue_up 

up_is_black:    
    cmp map[bx],'1'
    je up_set_fill_flag 
    jne skip_up_ 
      
up_set_fill_flag:
    mov fill_flag,1h   
    
skip_up_:  
    add bx,50h        
    cmp number,0h
    je up_set_start
    jne up_start_is_setted     
    
up_set_start:
    mov start_x,dl
    mov start_y,dh    
    
up_start_is_setted:    
    push bx
    add number,2h    
    mov map[bx],'2'
    inc bx
    mov map[bx],10011001b
    inc bx     
    jmp continue_up 
 
continue_up:        
    sub bx,52h 
    mov map[bx],'0'
    inc bx
    mov map[bx],10101010b
    inc bx       
    sub bx,2h
    lea si,map[bx]
    mov cx,2h     
    sub di,0A0h
    repe movsb    
    add bx,50h
    lea si,map[bx]
    mov cx,2h     
    add di,9Eh
    repe movsb 
    sub di,0A2h  
    sub bx,50h  
    dec dh   
    cmp fill_flag,0h
    ja fill  
    jmp move_cycle

down:
    cmp dh,16h
    je move_cycle        
    sub bx,2h   
    cmp map[bx],'1'
    je down_stay_on_purple 
    jne skip_down    
    
down_stay_on_purple:
    add bx,4h    
    cmp map[bx],'1'
    je down_add_4Eh 
    
down_add_4Eh:
    add bx,4Eh
    jmp down_is_purple 
      
skip_down:    
    add bx,52h
    cmp map[bx],'1'
    je down_is_purple 
    cmp map[bx],'2'
    je end_move
    cmp map[bx],'3'  
    je down_is_black 
    cmp map[bx],'4'
    je end_move   
             
down_is_purple: 
    cmp map[bx-0A0h],'2'
    je down_is_black    
    sub bx,50h
    mov map[bx],'1'
    inc bx
    mov map[bx],11011101b
    inc bx    
    jmp continue_down 

down_is_black: 
    cmp map[bx],'1'
    je down_set_fill_flag 
    jne skip_down_ 
      
down_set_fill_flag:
    mov fill_flag,1h 
    
skip_down_:  
    sub bx,50h 
    cmp number,0h
    je down_set_start
    jne down_start_is_setted    
    
down_set_start:
    mov start_x,dl
    mov start_y,dh      
    
down_start_is_setted:    
    push bx
    add number,2h    
    mov map[bx],'2'
    inc bx
    mov map[bx],10011001b
    inc bx     
    jmp continue_down 
    
continue_down:   
    add bx,4Eh 
    mov map[bx],'0'
    inc bx
    mov map[bx],10101010b 
    inc bx       
    sub bx,52h
    lea si,map[bx]
    mov cx,2h     
    repe movsb
    add bx,50h 
    lea si,map[bx]
    mov cx,2h     
    add di,9Eh
    repe movsb 
    sub di,2h  
    inc dh          
    cmp fill_flag,0h
    ja fill_to_down
    jmp move_cycle 

fill:  
    mov fill_flag,0h 
    mov memory_bx,bx 
    mov cx,number 
    mov number,0h
    cmp dl,start_x
    jb fill_to_left
    ja fill_to_right

fill_to_left:       
    pop bx 
    inc number_of_element 
      
fill_to_left_cycle:  
    cmp map[bx],'1'
    je continue_fill_to_left 
    cmp map[bx],'2'
    je check_first_left
    jne skip_check_left
    
check_first_left:
    cmp number_of_element,1h 
    jne continue_fill_to_left  
    
check_left:
    cmp map[bx-4Eh],'1' 
    jne continue_fill_to_left   
    
skip_check_left: 
    inc number_of_element
    mov map[bx],'1'
    inc bx
    mov map[bx],11011101b
    inc bx    
    
    inc filled_celles
    
    cmp map[bx],'1'
    je continue_fill_to_left 
    jne fill_to_left_cycle  
    
continue_fill_to_left:
    mov number_of_element,0h        
    cmp map[bx],'2'
    je blue_to_purple_left
    jne skip_element_left  
    
blue_to_purple_left:
    mov map[bx],'1'
    inc bx
    mov map[bx],11011101b
    inc bx 
    inc filled_celles             
    
skip_element_left:        
    sub cx,2h     
    cmp cx,0h 
    jne fill_to_left   

draw_filled_area_left:
    call draw    
    pusha    
    mov ax,64h
    mul filled_celles
    div all    
    call hex_to_str
    popa        
    mov bx,memory_bx 
    jmp move_cycle 
      
fill_to_right:  
    pop bx 
    inc number_of_element  
     
fill_to_right_cycle:  
    cmp map[bx],'1'
    je continue_fill_to_right 
    cmp map[bx],'2'
    jne skip_check_right  
    
check_first_right:
    cmp number_of_element,1h 
    jne continue_fill_to_right
    
check_right:
    cmp map[bx-52h],'1' 
    je skip_check_right
    jne continue_fill_to_right 
    
skip_check_right: 
    inc number_of_element
    mov map[bx],'1'
    inc bx
    mov map[bx],11011101b
    sub bx,3h     
    inc filled_celles    
    cmp map[bx],'1'
    jne fill_to_right_cycle   
    
continue_fill_to_right:
    mov number_of_element,0h        
    cmp map[bx],'2'
    je blue_to_purple_right
    jne skip_element_right  
    
blue_to_purple_right:
    mov map[bx],'1'
    inc bx
    mov map[bx],11011101b
    sub bx,3h             
    inc filled_celles   
    
skip_element_right:        
    sub cx,2h     
    cmp cx,0h  
    jne fill_to_right   

draw_filled_area_right:
    call draw           
    pusha    
    mov ax,64h
    mul filled_celles
    div all    
    call hex_to_str
    popa    
    mov bx,memory_bx  
    jmp move_cycle   
    
fill_to_down:
    mov fill_flag,0h 
    mov memory_bx,bx 
    mov cx,number 
    mov number,0h
    cmp dl,start_x
    ja fill_to_left
    jb fill_to_right  
    jmp fill_to_right

end_move:  
    cmp number,0h
    je _game_over_      
clear_stack:
    pop bx
    sub number,2h
    cmp number,0h
    jne clear_stack   
_game_over_:          
    cmp win,0h
    ja _win_
    lea si,game_over
    mov di,26h   
    mov cx,12h
    repe movsb
    jmp ret_from_move
_win_:
    lea si,win_message
    mov di,26h   
    mov cx,6h  
    repe movsb    
ret_from_move:    
    popa    
    ret     
move endp
  
start:        
    pusha
    mov ax,@data
    mov ds,ax
    push 0B800h
    pop es
    mov di,0h     
    mov ah,0h
    mov al,3h
    int 10h              
    mov ah,1h
    mov ch,20h
    int 10h    
    mov ah,2h
    mov bh,0h
    mov dh,0h
    mov dl,0h
    int 10h                        
    mov di,0h              
    mov cx,18h          
    lea si,filled_area  
    repe movsb            
    mov ax,64h
    mul filled_celles
    div all    
    call hex_to_str     
    call draw
    call move    
    popa      
    mov ax,4C00h
    int 21h
        
    .data  
win_message db 'W',00001111b,'I',00001111b,'N',00001111b
win dw 0h   
over dw 0h     
left_down dw 1h
left_up dw 0h
right_down dw 0h
right_up dw 0h    
filled_celles dw 74h  
all dw 320h     
enemy_bx dw 398h   
enemy_di dw 910h    
fill_flag dw 0h 
number_of_element dw 0h
memory_bx dw 0h
number dw 0h 
start_x db 0h
start_y db 0h                                
filled_area db 'F',00001111b,'i',00001111b,'l',00001111b,'l',00001111b,'e',00001111b,'d',00001111b,' ',00001111b,'a',00001111b,'r',00001111b,'e',00001111b,'a',00001111b,':',00001111b  
game_over db 'G',00001111b,'A',00001111b,'M',00001111b,'E',00001111b,' ',00001111b,'O',00001111b,'V',00001111b,'E',00001111b,'R',00001111b
map db '0',10101010b,
db 28h dup('1',11011101b)
db 26h dup('3',00000000b)
db 2h dup('1',11011101b)
db 26h dup('3',00000000b)
db 2h dup('1',11011101b)
db 26h dup('3',00000000b)
db 2h dup('1',11011101b)
db 26h dup('3',00000000b)
db 2h dup('1',11011101b)
db 26h dup('3',00000000b)
db 2h dup('1',11011101b)
db 26h dup('3',00000000b)
db 2h dup('1',11011101b)
db 26h dup('3',00000000b)
db 2h dup('1',11011101b)
db 26h dup('3',00000000b)
db 2h dup('1',11011101b)
db 26h dup('3',00000000b)
db 2h dup('1',11011101b)
db 26h dup('3',00000000b)
db 2h dup('1',11011101b)
db 13h dup('3',00000000b) 
db 1h dup('4',11111111b)
db 12h dup('3',00000000b)
db 2h dup('1',11011101b)
db 26h dup('3',00000000b)
db 2h dup('1',11011101b)
db 26h dup('3',00000000b)
db 2h dup('1',11011101b)
db 26h dup('3',00000000b)
db 2h dup('1',11011101b)
db 26h dup('3',00000000b)
db 2h dup('1',11011101b)
db 26h dup('3',00000000b)
db 2h dup('1',11011101b)
db 26h dup('3',00000000b)
db 2h dup('1',11011101b)
db 26h dup('3',00000000b)
db 29h dup('1',11011101b)
end start    