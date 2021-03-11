# 1 "mimacro.s"
# 1 "<built-in>" 1
# 1 "mimacro.s" 2
puertoa EQU PORTA
puertob EQU PORTB
puertoc EQU PORTC
puertod EQU PORTD
puertoe EQU PORTE
;

encender macro pin,puerto
    bsf puerto,pin
    endm
apagar macro pin,puerto
    bcf puerto,pin
    endm

;

banco macro payasito
;banco 0
if payasito==0
BCF STATUS, RP0
BCF STATUS, RP1
endif

if payasito==1
;banco 1
BSF STATUS, RP0
BCF STATUS, RP1
endif

if payasito==2
;banco 2
BCF STATUS, RP0
BSF STATUS, RP1
endif

if payasito==3
;banco 3
BSF STATUS, RP0
BSF STATUS, RP1
endif

endm

;
csir macro registro1,registro2,direcc
    movf registro2,0
    subwf registro1,0
    btfsc STATUS,Z
    goto direcc
endm
; Compara registro con un valor y se va a la rutina direccion si son iguales

csi macro registro1,valor,direccion
    movlw valor
          subwf registro1,0
          btfsc STATUS,Z
          goto direccion
endm

enviaradisplay macro numnum
 MOVLW numnum
 CALL TABLAANODO
 MOVWF PORTD
endm

enviarcdisplay macro numnum
 MOVLW numnum
 CALL TABLACATODO
 MOVWF PORTD
endm

on_lib_retardos_ms macro
 CALL CONFTMR0TEMP
endm

retardo_ms macro valor
 MOVLW valor
 CALL RETARDOLIBRE_mS
endm

;Conversor de Binario a BCD. La respuesta se guarda en registros bcd_unidad, bcd_decena, bcd_centena
convertir_a_bcd macro registro
 MOVF registro,0
 CALL binario_a_bcd
endm
