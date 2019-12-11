segment .bss

cad1 resb 50
mens	resb 100
longi	resb 1
decenas	resb 1
resultado	resb 2

segment .data

mens2 db "longitud de cadena es: " 

segment .txt

global _start

_start:

	mov	eax,"0"			;inicializamos las variables en 0
	mov	[longi],eax
	mov 	[decenas],eax

;=======================================================================================================================

	mov	edx,100d		;buffer para ingresar cadena de maximo 100 caracteres 
	mov	ecx,cad1		;pasamos la direccion de cad1 a ecx
	mov	ebx,0			;entrada estandar
	mov	eax,3			;sys_read
	int	0x80			;interrupcion

;=======================================================================================================================
	mov	esi,cad1		;direccion de cad1 al indice
	call	contar
	call	atoi

;=======================================================================================================================

	mov	edx,24d			;buffer para mensaje
	mov	ecx,mens2
	mov	ebx,1			;salida estandar
	mov	eax,4			;sys_write
	int	0x80			;interrupcion del sistema

;=======================================================================================================================

	mov	edx,2			;buffer para el resultado
	mov	ecx,resultado
	mov	ebx,1
	mov	eax,4
	int	0x80

	mov	eax,1			;sys_exit
	int	0x80			;interrupcion del sistema

;=======================================================================================================================


contar:					;cuenta unidades, guarda su valor en longi en ascii y cuenta numero de decenas

	mov	ecx,0			;iniciar ecx en 0 para contar las decenas
l1:
	mov	eax,[esi]		;guardar la letra de esi (que esta en cad1) en eax
	cmp	eax,0Ah			;verificar si es un salto de linea, es decir si ya se llego al final de la palabra
	je	regresa			;si es asi ir a la etiqueta regresa
	inc	esi			;avanzar el indice esi dentro del la cad1
	mov	eax,[longi]		;guardar el contenido de longi (unidades) en eax
	inc	eax			;incrementar ese valor en uno
	mov	[longi],eax		;sobreescribir el nuevo valor en el contenido de longi
	mov	ch,[longi]		;en ch guardar ese valor
	cmp	ch,":"			;verificar si es mayor a 9 (ascii)
	je	incremento		;si es asi ve a incremento
	jne	l1			;si no repite en l1

incremento:

	mov	ch,"0"			;en ch guradar un cero cuando se supere el 9 en ascii
	mov	[longi],ch		;se reinicia longi en 0
	inc	ecx			;se incrementa el contador de decenas
	jmp	l1			;se regresa a l1 para seguir contando

regresa:
	
	ret				;sale de subrutina contar


;=======================================================================================================================

atoi:					;cuenta numero de decenas y le cancatena las unidades, guardandolas en 
					;la variable resultado

l2:
	cmp	ecx,0			;verifica si ecx esta en 0
	je	regresa2		;si es asi ve a regresa2
	mov	eax,[decenas]		;el 0 de decenas a eax
	inc	eax			;incrementar ese valor en uno
	mov	[decenas],eax		;sobreescribir nuevi valor en decenas
	dec	ecx			;restar en uno el valor de ecx
	jne	l2			;cuando ecx es diferente de 0 repite a l2

regresa2:
	mov	esi,decenas		;poner indice en la direccion de decenas
	mov	edi,resultado		;poner indice destino en la direccion de resultado
	mov	eax,[esi]		;guardar el contenido "[]" de esi en eax(usandolo como auxiliar)
	mov	[edi],eax		;guardar el contenido de eax en el contenido de edi que apunta a resultado
	inc	edi			;moverse una posicion en el arrego resultado
	mov	esi,longi		;poner undice destino en la direccion de longi
	mov	eax,[esi]		;guardar el contenido "[]" de esi en eax(usandolo como auxiliar) 
	mov	[edi],eax		;guardar contenido de eax en el contenido de edi que apunta a la segunda posi de resultado
	ret				;salir de la subrutina
