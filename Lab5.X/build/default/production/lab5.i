# 1 "lab5.s"
# 1 "<built-in>" 1
# 1 "lab5.s" 2
INCLUDE <P16F877A.INC>
LIST P=16F877A
INCLUDE <mimacro.INC>
ORG 0;
CBLOCK 0X20
MEMORIA ; Memoria para almacenar valor
ENDC

banco 1 ;Nos vamos al banco 1
MOVLW b'11010111' ; activo libreria de retardos por tmr0
MOVWF OPTION_REG ; Configuración para el TMR0 para los retardos
CLRF TRISD ; Puerto D como salida
CLRF TRISC ; Puerto C como salida
MOVLW B'11111111'
MOVWF TRISB
banco 0 ; Regreso al banco 0
CLRF PORTD ; Limpio puertoD
CLRF PORTB
MOVLW B'11100000' ; Limpio puerto C
MOVWF PORTC ;

;
PROGRAMA ;Titulo de bucle
;MOVLW d'124' ;Valor a escribir en 3 displays ENTRE 0 A 255
;MOVWF MEMORIA ;Guarfamos valor en memoria
convertir_a_bcd PORTB ;Comando para decodificar el valor en BCD

ESCRIBEUNIDAD ;Título
encender 5,puertoc ;Apagamos display de centena
MOVF bcd_unidad,0 ;Extraemos valor de respuesta almacenado en bcd_unidad
CALL TABLACATODO ; Convertimos el valor en 7 segmentos tipo cátodo
MOVWF PORTD ; Movemos el valor de respuesta en puerto D
apagar 7,puertoc ; Encendemos display de Unidad
retardo_ms .20 ; Mantenemos el valor durante 20 milisengundos

ESCRIBEDECENA ;título
encender 7,puertoc ;Apagamos display de unidad
MOVF bcd_decena,0 ; Extraemos valor de respuesta almacenado en bcd_decena
CALL TABLACATODO ;Convertimos el valor de esa respuesta en 7 segmentos
MOVWF PORTD ;Movemos la respuesta de la tabla al puerto D
apagar 6,puertoc ; Encendemos display de decenas
retardo_ms .20 ;Mantenemos el valor durante 20 milisengundos

ESCRIBECENTENA ;Título
encender 6,puertoc ; Apagamos display de decenas
MOVF bcd_centena,0 ; Extraemos valor de respuesta almacenado en bcd_centena
CALL TABLACATODO ; Convertimos el valor en 7 segmentos para display
MOVWF PORTD ; Movemos la respuesta convertida al puerto D
apagar 5,puertoc ; Encendemos el display de Centena
retardo_ms .20 ; Mantenemos el valor durante 20 milisengundos

GOTO PROGRAMA ; Repetimos el bucle

INCLUDE <conversor.ASM> ;Incluimos libreria de conversor binario a BCD
INCLUDE <RETARDOS.ASM> ; Incluimos libreria de retardos
INCLUDE <display.ASM> ; Incluimos libreria para display
END
