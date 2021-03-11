PROCESSOR 16F887
#include <xc.inc>

; configuración word1
 CONFIG FOSC=INTRC_NOCLKOUT //Oscilador interno sin salidas
 CONFIG WDTE=OFF	    //WDT disabled (reinicio repetitivo del pic)
 CONFIG PWRTE=ON	    //PWRT enabled (espera de 72ms al iniciar
 CONFIG MCLRE=OFF	    //pin MCLR se utiliza como I/O
 CONFIG CP=OFF		    //sin protección de código
 CONFIG CPD=OFF		    //sin protección de datos
 
 CONFIG BOREN=OFF	    //sin reinicio cuando el voltaje baja de 4v
 CONFIG IESO=OFF	    //Reinicio sin cambio de reloj de interno a externo
 CONFIG FCMEN=OFF	    //Cambio de reloj externo a interno en caso de falla
 CONFIG LVP=ON		    //Programación en bajo voltaje permitida
 
;configuración word2
  CONFIG WRT=OFF	//Protección de autoescritura 
  CONFIG BOR4V=BOR40V	//Reinicio abajo de 4V 

 UP	EQU 0
 DOWN	EQU 1	
	
reiniciar_Tmr0 macro
    banksel TMR0
    movlw   221	;10 ms 
    movwf   TMR0
    bcf	    T0IF
    endm
    
  PSECT udata_bank0 ;common memory
    var:	DS  1 ;1 byte apartado
    displayvar2:    DS	2;
    banderas:	DS  1
    nibble:	DS  2
    display_var:    DS	2
    centena:	DS  1
    centena1:	DS  1
    decena:	DS  1
    decena1:	DS  1
    unidad1:	DS  1
    unidad:	DS  1
    V1:		DS  1
  PSECT udata_shr ;common memory
    w_temp:	DS  1;1 byte apartado
    STATUS_TEMP:DS  1;1 byte
  
  PSECT resVect, class=CODE, abs, delta=2
  ;----------------------vector reset------------------------
  ORG 00h	;posición 000h para el reset
  resetVec:
    PAGESEL main
    goto main
    
  PSECT intVect, class=CODE, abs, delta=2
  ;----------------------interripción reset------------------------
  ORG 04h	;posición 0004h para interr
  push:
    movf    w_temp
    swapf   STATUS, W
    movwf   STATUS_TEMP
  isr:
    btfsc   RBIF
    call    int_ioCB
    
    btfsc   T0IF
    call    Interr_Tmr0
  pop:
    swapf   STATUS_TEMP, W
    movwf   STATUS
    swapf   w_temp, F
    swapf   w_temp, W
    retfie
;---------SubrutinasInterrupción-----------
int_ioCB:
    banksel PORTB
    btfss   PORTB, UP
    incf    PORTA
    btfss   PORTB, DOWN
    decf    PORTA
    bcf	    RBIF
    return
Interr_Tmr0:
    reiniciar_Tmr0	;50 ms
    bcf     STATUS, 0
    clrf    PORTB
    btfsc   banderas, 1 
    goto    display0
    btfsc   banderas, 2
    goto    display1
    btfsc   banderas, 3
    goto    displaycentena
    btfsc   banderas, 4
    goto    displaydecena
    btfsc   banderas, 5
    goto    displayunidad
    movlw   00000001B
    movwf   banderas
siguientedisplay:
    RLF	    banderas, 1
    return
    
display0:
    movf    display_var, w
    movwf   PORTC
    bsf	    PORTB, 2 
    goto    siguientedisplay
display1:
    movf    displayvar2, w
    movwf   PORTC
    bsf	    PORTB, 3
    goto    siguientedisplay
displaycentena: 
    movf    centena1, w
    movwf   PORTD
    bsf	    PORTB, 4
    goto    siguientedisplay
displaydecena:
    movf    decena1, w
    movwf   PORTD
    bsf	    PORTB, 5
    goto    siguientedisplay
displayunidad:
    movf    unidad1, w 
    movwf   PORTD
    bsf	    PORTB,6
    goto    siguientedisplay    
    
  PSECT code, delta=2, abs
  ORG 100h	;Posición para el código
 ;------------------ TABLA -----------------------
  Tabla:
    clrf  PCLATH
    bsf   PCLATH,0
    andlw 0x0F
    addwf PCL
    retlw 00111111B          ; 0
    retlw 00000110B          ; 1
    retlw 01011011B          ; 2
    retlw 01001111B          ; 3
    retlw 01100110B          ; 4
    retlw 01101101B          ; 5
    retlw 01111101B          ; 6
    retlw 00000111B          ; 7
    retlw 01111111B          ; 8
    retlw 01101111B          ; 9
    retlw 01110111B          ; A
    retlw 01111100B          ; b
    retlw 00111001B          ; C
    retlw 01011110B          ; d
    retlw 01111001B          ; E
    retlw 01110001B          ; F
 
  ;---------------configuración------------------------------
  main: 
    call    config_io	
    call    config_reloj
    call    config_IOChange
    call    config_tmr0
    call    config_InterrupEnable  
    banksel PORTA 
    ;movlw   01011011B
    ;movwf   unidad1
    ;movlw   00000110B
    ;movwf   decena1
    ;movlw   00111111B
    ;movwf   centena1
;----------loop principal---------------------
 loop:
    movf    PORTA, w
    movwf   var
    movwf   V1
    
    call    separar_nibbles
    call    config_displays
    call    divcentenas
    call    displaydecimal

    goto    loop    ;loop forever 
;------------sub rutinas--------------------
displaydecimal:
    movf    centena, w
    call    Tabla
    movwf   centena1
    movf    decena, w
    call    Tabla
    movwf   decena1
    movf    unidad, w
    call    Tabla
    movwf   unidad1
    return
divcentenas:
    clrf    centena
    movlw   01100100B    ;ASIGNAMOS EL VALOR DE "100" W
    subwf   V1, 1        ;RESTMOS W DE F
    btfss   STATUS,0   
    ;return		;AQUIIIIIIIIIII
    goto    DECENAS
    incf    centena, 1
    goto    $-5
DECENAS:
    clrf    decena   
    movlw   01100100B 
    addwf   V1
    movlw   00001010B
    subwf   V1,1
    btfss   STATUS,0
    ;return
    goto    UNIDADES
    incf    decena, 1
    goto    $-5  
UNIDADES:
    clrf    unidad
    movlw   00001010B
    addwf   V1
    movlw   00000001B
    subwf   V1,1
    btfss   STATUS, 0
    return
    incf    unidad, 1
    goto    $-5
separar_nibbles:
    movf    var, w
    andlw   0x0f
    movwf   nibble
    swapf   var, w
    andlw   0x0f 
    movwf   nibble+1
    return
config_displays:
    movf    nibble, w
    call    Tabla
    movwf   display_var
    movf    nibble+1, w
    call    Tabla
    movwf   displayvar2
    return
config_IOChange:
    banksel TRISA
    bsf	    IOCB, UP
    bsf	    IOCB, DOWN 
    
    banksel PORTA
    movf    PORTB, W	;Condición mismatch
    bcf	    RBIF
    return
config_io:
    bsf	    STATUS, 5   ;banco  11
    bsf	    STATUS, 6	;Banksel ANSEL
    clrf    ANSEL	;pines digitales
    clrf    ANSELH
    
    bsf	    STATUS, 5	;banco 01
    bcf	    STATUS, 6	;Banksel TRISA
    clrf    TRISA	;PORTA A salida
    clrf    TRISC
    clrf    TRISD
    bsf	    TRISB, UP
    bsf	    TRISB, DOWN
    bcf	    TRISB, 2
    bcf	    TRISB, 3
    bcf	    TRISB, 4
    bcf	    TRISB, 5
    bcf	    TRISB, 6
    ;bcf	    TRISB, 6
    
    bcf	    OPTION_REG,	7   ;RBPU Enable bit - Habilitar
    bsf	    WPUB, UP
    bsf	    WPUB, DOWN
    
    bcf	    STATUS, 5	;banco 00
    bcf	    STATUS, 6	;Banksel PORTA
    clrf    PORTA	;Valor incial 0 en puerto A
    clrf    PORTC
    clrf    PORTD
    return
     
 config_tmr0:
    banksel OPTION_REG   ;Banco de registros asociadas al puerto A
    bcf	    T0CS    ; reloj interno clock selection
    bcf	    PSA	    ;Prescaler 
    bsf	    PS2
    bsf	    PS1
    bsf	    PS0	    ;PS = 111 Tiempo en ejecutar , 256
    
    reiniciar_Tmr0  ;Macro reiniciar tmr0
    return  
    
 config_reloj:
    banksel OSCCON	;Banco OSCCON 
    bsf	    IRCF2	;OSCCON configuración bit2 IRCF
    bsf	    IRCF1	;OSCCON configuracuón bit1 IRCF
    bcf	    IRCF0	;OSCCON configuración bit0 IRCF
    bsf	    SCS		;reloj interno , 4Mhz
    return

config_InterrupEnable:
    bsf	    GIE		;Habilitar en general las interrupciones, Globales
    bsf	    RBIE	;Se encuentran en INTCON
    bcf	    RBIF	;Limpiamos bandera
    bsf	    T0IE
    bcf	    T0IF
    return
 
end