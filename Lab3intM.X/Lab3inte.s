PROCESSOR 16F887
    #include "xc.inc"
  
    CONFIG FOSC = INTRC_NOCLKOUT
    CONFIG WDTE = OFF       
    CONFIG PWRTE = ON      
    CONFIG MCLRE = OFF     
    CONFIG CP = OFF         
    CONFIG CPD = OFF        
    CONFIG BOREN = OFF      
    CONFIG IESO = OFF       
    CONFIG FCMEN = OFF      
    CONFIG LVP = ON        

    ;configuration word 1
    CONFIG WRT = OFF
    CONFIG BOR4V=BOR40V
    
PSECT udata_bank0 
    
  CONT1: ds 1 
  CONT2: ds 1

PSECT udata_shr 
  STATUS_TEMP: DS 1
  W_TEMP:      DS 1 

PSECT resVect, class=CODE, abs, delta = 2
;-------------vector res---------------------------
ORG 00h
    resetVec: 
	PAGESEL main
	goto    main
;----------------------Interrupcion VEC-----------------------
PSECT intVect, class = CODE,abs, delta = 2 
ORG 04h

 push: 
    MOVWF W_TEMP 
    SWAPF STATUS, W
    MOVWF STATUS_TEMP
    
 isr:
    btfsc  RBIF 
    call   int_rb 
    
    
 pop:
    SWAPF STATUS_TEMP, W
    MOVWF STATUS 
    SWAPF W_TEMP, F 
    SWAPF W_TEMP, W
    RETFIE
 ;---------------interrupcion----------------------------
 int_rb:
    btfss  PORTB, 7
    incf   PORTA
    btfss  PORTB, 0
    decf   PORTA
    movf   PORTB, W 
    bcf    RBIF
    return
 
    
PSECT code, delta = 2, abs 
 ORG 100h
   
;-----------Main-----------------
    
main:    
     
      /*call frecuencia	    //llamamos la funcion frecuencia
      call timer0	    //llamamos la funcion timer0
      btfss T0IF            //llamamos la funcion T0IF
      goto  $-1
      call  empezar         //llamamos la funcion empezar
      incf  PORTD          //incrementamos el puertob*/
      call SETUP
      call rbioc 
               //vamos al main
;--------------------Interrupcion----------------------
loop: 
    call DELAY
    goto loop
rbioc: 
    banksel TRISA
    movlw   10000001B
    movwf   IOCB 
    
    banksel PORTB
    movf    PORTB, W
    bcf     RBIF 
    bsf     GIE 
    bsf     RBIE 
    return
    
SETUP:  
    banksel ANSEL
    CLRF ANSEL    ;entradas digitales
    CLRF ANSELH   ;entradas digitales 
    
    
   banksel TRISA
  
    bcf TRISA, 0
    bcf TRISA, 1
    bcf TRISA, 2
    bcf TRISA, 3
    
    bsf TRISB, 0
    bsf TRISB, 1
    bsf TRISB, 2
    bsf TRISB, 3
    bsf TRISB, 7
    
    bcf   OPTION_REG, 7 //encendemos el bit del pull up 
    movlw 0xff
    movwf WPUB
    
    
    banksel PORTA
    clrf PORTA  
    return
  
;--------------------Tabla----------------------
    
/*display:
   CLRF  PCLATH              ;limpiamos el registro
   bsf   PCLATH, 0           ;ponemos en 1 el bit 0 del registro
   ADDWF PCL                 ;sumamos 1 al pcl para poder determinar que sale ne l display
   RETLW 0000B ;numero_0
   RETLW 1000B ;numero_1
   RETLW 0100B ;numero_2
   RETLW 1100B ;numero_3
   RETLW 0010B ;numero_4
   RETLW 1010B ;numero_5
   RETLW 0110B ;numero_6
   RETLW 1110B ;numero_7
   RETLW 0001B ;numero_8
   RETLW 1001B ;numero_9
   RETLW 0101B ;numero_A
   RETLW 1101B ;numero_B
   RETLW 0011B ;numero_C
   RETLW 1011B ;numero_D
   RETLW 0111B ;numero_E
   RETLW 1111B ;numero_F
   return*/
    
;-----------Configuraciones timer y oscilador-----------------

 
    
/*timer0:
    banksel OPTION_REG //nos vamos al banko 1
    bcf     T0CS //escogemos los valores del timer
    bcf     PSA
    bsf     PS2
    bsf     PS1
    bcf     PS0
    banksel PORTA
    call    empezar
    return
 
 frecuencia:
    banksel OSCCON //nos vamos al bancoo 1 
    bcf     IRCF0  //escogemos los valores del osscon
    bcf     IRCF1
    bcf     IRCF2
    bsf     SCS 
    return
    
    
 empezar:
    movlw   226  //movemos la literal al timer 0
    movwf   TMR0
    bcf     T0IF
    return*/
    
;-----------------------------Alarma---------------------------

DELAY:
    
    MOVLW 0Xfa     //movemos una literal 
    MOVWF CONT1   //movemos la literal cont1
    MOVLW 0X0d    //movemos otra literal 
    MOVWF CONT2   //movemos la literal al cont2
    
LOOP:
    DECFSZ CONT1, 1
    GOTO LOOP
    DECFSZ CONT2, 1
    GOTO LOOP
    NOP
RETURN

END

    





