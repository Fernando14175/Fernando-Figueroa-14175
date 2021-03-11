
tertulia equ 0


BSF STATUS,RP0
MOVLW 11010111B
MOVWF OPTION_REG
BCF STATUS,RP0
CLRF tertulia
RETURN

 RETARDOLIBRE_mS:        ; Subrutina de retardo
 NOP                 ;
 MOVWF tertulia      ;direccion memoria
 DECREMENTAR
 apagar TMR0IF,INTCON
 MOVLW d'236' ;<- Valor calculado por fórmula para 1ms
 MOVWF TMR0  ;<- Llevamos el valor a TMR0 desde este momento ya está contando
 COMPROBAR   ;Subrutina de comprobación
 BTFSS INTCON,TMR0IF ; ¿el pin TMR0IF es 1?
 GOTO COMPROBAR      ; Respuesta falsa, me voy a seguir testeando.
 DECFSZ tertulia,1
 GOTO DECREMENTAR
 apagar Z,STATUS
 RETURN ; Respuesta verdadera, regreso a donde llamaron.


