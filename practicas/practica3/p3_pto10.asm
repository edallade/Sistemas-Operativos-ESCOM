section .bss

cad1 resb 50			;variables
cad2 resb 50			;para almacear las cadenas
cad3 resb 50

dest resb 150	

section .text
   global _start

_start:

	mov	edx,150		;buffer para guardar las cadenas 
	mov	ecx,cad1	;direccion de cad1 a ecx para ser capturada
	mov	ebx,0		;entrada estandar
	mov	eax,3		;llamada al sistema read
	int	0X80		;iterrupcion al sistema


	mov	ecx,cad2
	mov	ebx,0
	mov	eax,3
	int	0X80

	mov	ecx,cad3
	mov	ebx,0
	mov	eax,3
	int	0x80

	mov	bh,200		;iniciamos el registro bh en 200 para el contador 
	mov	edi,dest	;poner indice destino al inicio de la variable destino	edi=dest

l1:

	mov	esi,cad1	;indice al inicio de cadena1, esi=cad1
	call	cont		;llamada a la subrutina que mueve esi 
	mov	eax,[esi]	;contenido de esi (cad1 o cad2 o cad3)a eax 
	mov	[edi],eax	;copiar el cotenido de eax al contenido del indice destino edi

	mov	esi,cad2
	call	cont
	mov	eax,[esi]
	mov	[edi],eax

	mov	esi,cad3
	call	cont
	mov	eax,[esi]
	mov	[edi],eax
	
	cmp	eax,0Ah		;verificar que esi en cad1|cad2|cad3 llego al final de la palabra
	inc	bh		;incrementar registro bh usado como referencia para el contador
	jne	l1		;si no se ha llegado al final de la tercera palabra repite

imp:
	xor	edx,edx		;limpiar el buffer edx, si no se imprimia a demas de "dest" lo 
	mov	edx,50		;ultimo ingresado por teclado (cad3)
	mov	ecx,dest	;mover la direccion de dest a ecx para imprimir el resultado
	mov	ebx,1		;salida estandar
	mov	eax,4		;llamada al sistema write
	int	0x80		;interrupcion del sistema





   	mov eax,1		;sitema exit
   	int 0x80		;interrupcion del sitema

cont:

	mov	ch,200		;iniciar registro ch en 200
l2:
				
	cmp	ch,bh		;comparar los registros para numero de inrementos del indice esi
	je	retu		;cuando sean iguales regresa de la subrutina
	inc	esi		;mueve el indice esi dentro de las cad1,2,3
	inc	ch		;incrementa ch para detener el l2 
	jne	l2


retu:
	inc	edi		;mover indice en la cadena dest

	ret		
