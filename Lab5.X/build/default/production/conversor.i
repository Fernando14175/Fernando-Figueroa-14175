# 1 "conversor.s"
# 1 "<built-in>" 1
# 1 "conversor.s" 2

bcd_unidad equ 0
bcd_decena equ 0
bcd_centena equ 0


binario_a_bcd macro
    MOVWF bcd_unidad ;Carga el número binario a convertir
    CLRF bcd_centena ;Borra registro
    CLRF bcd_decena ;Borra registro
BCD_Resta10
    MOVLW .10 ;A las unidades de les va restando
    SUBWF bcd_unidad,0 ;10 en cada pasada
    BTFSS STATUS,C ;C=0? si- entonces bcd_unidad>=0
    GOTO BIN_BCD_Fin ;No- entonces se acabo
BCD_IncrementarDecenas
    MOVWF bcd_unidad ;Recupera lo que queda por restar
    INCF bcd_decena,1 ;Incrementa las decenas
    MOVLW .10
    SUBWF bcd_decena,0 ;Comprueba si a llegado a 10
    BTFSS STATUS,C ;C=1? si- entonces bcd_decena>=0
    GOTO BCD_Resta10 ;No- entonces resta 10 a las unidades
BCD_IncrementarCentenas
    CLRF bcd_decena ;Pone a cero las decenas
    INCF bcd_centena,1 ;Incrementa las centenas
    GOTO BCD_Resta10 ;Resta 10 al número a convertir
BIN_BCD_Fin
    SWAPF bcd_decena,0 ;Intercambia nibles
    ADDWF bcd_unidad,0 ;Nible bajo=unidades / Nible alto=decenas
    RETURN
endm
