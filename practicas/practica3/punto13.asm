segment	.data

	eleccion db "eliga una opcion "
	long0	equ $-eleccion
	msj1 db "1.-Suma"
	long1	equ $-msj1
	msj2 db "2.-resta"
	long2	equ $-msj2
	msj3 db "3.-multiplicacion"
	long3	equ $-msj3
	msj4 db "4.-division"
	long4	equ $-msj4
	msj5 db "numero 1:"
	long5	equ $-msj5
	msj6 db "numero 2:"
	long6	equ $-msj6
	msj7 db "resultado:"
	long7	equ $-msj7
	msj8 db "eleccion invalida"
	long8	equ $-msj8
	salto	db	0Ah

segment .bss

	opcion	resb	2
	n1	resb	1
	n2	resb	1
	nr1	resb	1
	nr2	resb	1
	nr3	resb	1
	nr4	resb	1
	nr6	resw	1
	r1	resb	3
	dece resb	1
	uni	resb	1
	centen	resb	1
	contador resb	1
segment	.text

	global	_start:

_start:
;==========menu======================
menu:
	mov	edx,long0
	mov	ecx,eleccion
	call	imprime

	mov	edx,long1
	mov	ecx,msj1
	call	imprime

	mov	edx,long2
	mov	ecx,msj2
	call	imprime

	mov	edx,long3
	mov	ecx,msj3
	call	imprime

	mov	edx,long4
	mov	ecx,msj4
	call	imprime
;========================================

	mov	ecx,opcion
	mov	edx,1024
	mov	ebx,0
	mov	eax,3
	int	0x80

	
	mov	al,[opcion]
	cmp	al,"1"
	je	sumar
	cmp	al,"2"
	je	restar
	cmp	al,"3"
	je	multiplicar
	cmp	al,"4"
	je	dividir
	jne	error



salir:

	mov	eax,1
	int	0x80

;==========subrutina de sumar===============
sumar:

	mov	ecx,msj1
	mov	edx,long1
	call	imprime

	mov	ecx,msj5
	mov	edx,long5
	call	imprime

	mov	eax,3
	mov	ebx,0
	mov	edx,1024
	mov	ecx,n1
	int	0x80

	call	atoi
	mov	[nr3],cl

	mov	ecx,msj6
	mov	edx,long6
	call	imprime

	mov	eax,3
	mov	ebx,0
	mov	edx,1024
	mov	ecx,n1
	int	0x80

	call	atoi
	mov	[nr4],cl

	xor	ecx,ecx
	mov	cl,[nr3]
	mov	ch,[nr4]
	add	ch,cl


	mov	[r1],ch
call	itoa
	mov	ecx,r1
	mov	edx,3
	call	imprime

	jmp	salir

;============================================
;========subrutina de resta==================
restar:
	mov	ecx,msj2
	mov	edx,long2
	call	imprime

	mov	ecx,msj5
	mov	edx,long5
	call	imprime

	mov	eax,3
	mov	ebx,0
	mov	edx,1024
	mov	ecx,n1
	int	0x80
	call	atoi
	mov	[nr3],cl

	mov	ecx,msj6
	mov	edx,long6
	call	imprime


	mov	eax,3
	mov	ebx,0
	mov	edx,1024
	mov	ecx,n1
	int	0x80

	call	atoi
	mov	[nr4],cl

	xor	ecx,ecx
	mov	ch,[nr3]
	mov	cl,[nr4]
	sub	ch,cl


	mov	[r1],ch

	call	itoa
	mov	ecx,r1
	mov	edx,3
	call	imprime

	jmp	salir

;============================================
;==========subrutina de multiplicar=========
multiplicar:

	mov	ecx,msj3
	mov	edx,long3
	call	imprime

	mov	ecx,msj5
	mov	edx,long5
	call	imprime

	mov	eax,3
	mov	ebx,0
	mov	edx,1024
	mov	ecx,n1
	int	0x80
	call	atoi
	mov	[nr3],cl

	mov	ecx,msj6
	mov	edx,long6
	call	imprime


	mov	eax,3
	mov	ebx,0
	mov	edx,1024
	mov	ecx,n1
	int	0x80

	call	atoi
	mov	[nr4],cl

	xor	ecx,ecx
	mov	al,[nr3]
	mov	bl,[nr4]
	mul	bl


	mov	[r1],al
	mov	ch,[r1]
	call	itoa
	mov	ecx,r1
	mov	edx,3
	call	imprime

	jmp	salir


;=======subrutina de dividir========================
dividir:
	mov	ecx,msj4
	mov	edx,long4
	call	imprime

	mov	ecx,msj5
	mov	edx,long5
	call	imprime

	mov	eax,3
	mov	ebx,0
	mov	edx,1024
	mov	ecx,n1
	int	0x80
	call	atoi
	mov	[nr3],cl

	mov	ecx,msj6
	mov	edx,long6
	call	imprime


	mov	eax,3
	mov	ebx,0
	mov	edx,1024
	mov	ecx,n1
	int	0x80

	call	atoi
	mov	[nr4],cl

	xor	ecx,ecx
	mov	al,[nr3]
	mov	cl,[nr4]
	div	cl
    

	mov	[r1],al
	mov	ch,[r1]

	call	itoa
	mov	ecx,r1
	mov	edx,3
	call	imprime

	jmp	salir


;======atoi pasar de array a entero el numero=========
atoi:
	mov	esi,n1
	mov	ch,[esi]
	mov	cl,0d
	mov	al,0d
loop1:

	cmp	ch,0Ah
	je	unidades
	inc	esi
	mov	ch,[esi]
	inc	al
	jne	loop1

unidades:

	dec	esi
	mov	ch,[esi]
	dec	al
	sub	ch,"0"
	mov	[nr1],ch		;unidades en decimal en nr1
	cmp	al,0d
	je	salir1

	dec	esi
	mov	ch,[esi]
	dec	al
	sub	ch,"0"			;valor unitario de las decenas 
	mov	[nr2],ch
	mov	[contador],al

	mov	ebx,10
	mov	eax,[nr2]
	mul	ebx			;eax=eax*ebx

	xor	ecx,ecx
	mov	ecx,[nr1]
	add	ecx,eax			;sumar unidades y decenas1
	

	mov	ch,[contador]
	cmp	ch,0d
	je	sal

	xor	ch,ch
	dec	esi
	mov	ch,[esi]
	sub	ch,"0"
	mov	[n2],ch
	mov	bl,100
	mov	al,[n2]
	mul	bl

	add	cl,al
	ret


salir1:
	mov	ecx,[nr1]
	ret
sal:
	ret

;====================================================

;=======pasar el entero a arreglo para imprimir resultado=


itoa:
	mov	cl,"0"
	mov	[uni],cl
	mov	[dece],cl
	mov	[centen],cl
l3:
	cmp	ch,0
	je	concatenar
	dec	ch

	mov	cl,[uni]
	inc	cl
	mov	[uni],cl
	cmp	cl,":"
	je	decenas
	jne	l3
decenas:

	mov	cl,"0"	;reiniciar unidades
	mov	[uni],cl

	mov	cl,[dece]
	inc	cl
	mov	[dece],cl
	cmp	cl,":"
	je	centenas1
	jne	l3
centenas1:

	mov	cl,"0" ;reiniciar decenas
	mov	[dece],cl

	mov	cl,[centen]
	inc	cl
	mov	[centen],cl

	jmp	l3

concatenar:
	
	

	mov	esi,centen
	mov	edi,r1

	mov	cl,[esi]
	mov	[edi],cl
	inc	edi

	mov	esi,dece
	mov	cl,[esi]
	mov	[edi],cl
	inc	edi

	mov	esi,uni
	mov	cl,[esi]
	mov	[edi],cl

ret

;===================================================================


;=======imprimir en pantalla=============
imprime:

	mov	eax,4
	mov	ebx,1
	int	0x80

	mov	ecx,salto
	mov	edx,1
	mov	eax,4
	mov	ebx,1
	int	0x80

	ret
;===========================================




;=======mensaje de error===================
error:

	mov	ecx,msj8
	mov	edx,long8
	call	imprime
	jmp	salir
;===========================================
