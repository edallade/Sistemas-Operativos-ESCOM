segment .bss

cadenas 	resb 99
resultado	resb 1000
cont		resb 1
unidad		resb 1
decena		resb 1
longitud	resb 3
reves		resb 1000

segment .data

mens2 db "longitud de cadena es: "

segment .txt

global _start

_start:

	mov	al,"0"
	mov	[cont],al
	mov	[unidad],al
	mov	[decena],al
	mov	edx,100d
	mov	edi,resultado

l1:;====ciclo de ingreso 10 acenas========

	mov	ecx,cadenas
	mov	ebx,0
	mov	eax,3
	int	0x80

	call	concatena
	mov	al,[cont]
	inc	al
	mov	[cont],al
	cmp	al,":"
	jne	l1

	mov	al,0Ah
	mov	[edi],al

;============================================

	mov	edx,100
	mov	ecx,resultado
	call	imprime

	call	cuenta

	mov	edx,24d
	mov	ecx,mens2
	call	imprime

	mov	edx,3
	mov	ecx,longitud
	call	imprime

	call	invierte

	mov	edx,100
	mov	ecx,reves
	call	imprime

	mov	eax,1
	int	0x80






;======================================

concatena:

	mov	esi,cadenas
	mov	ah,[esi]

l2:
	cmp	ah,0Ah
	je	regresa
	mov	ah,[esi]
	mov	[edi],ah
	inc	esi
	inc	edi
	jne	l2

regresa:
	dec	edi
	ret


;=============================================

cuenta:
	mov	ecx,0
	mov	esi,resultado
unidades:
	mov	al,[esi]
	cmp	al,0Ah
	je	decenas

	inc	esi
	mov	eax,[unidad]
	inc	eax
	mov	[unidad],eax

	mov	ch,[unidad]
	cmp	ch,":"
	je	reinicia_unidades
	jne	unidades

reinicia_unidades:

	mov	ch,"0"
	mov	[unidad],ch
	inc	ecx
	jmp	unidades

decenas:

	cmp	ecx,0
	je	junta_uni_dec
	mov	eax,[decena]
	inc	eax
	mov	[decena],eax
	dec	ecx
	jne	decenas

junta_uni_dec:

	mov	esi,decena
	mov	edi,longitud
	mov	eax,[esi]
	mov	[edi],eax
	inc	edi

	mov	esi,unidad
	mov	eax,[esi]
	mov	[edi],eax

	inc	edi
	mov	eax,0Ah
	mov	[edi],eax

	ret


;============================================

imprime:


	mov	ebx,1
	mov	eax,4
	int	0x80
	ret

;=========INVIERTE============================

invierte:

	mov	ecx,0d
	mov	esi,resultado
	mov	al,[esi]
l4:
	cmp	al,0Ah
	je	exit_l4
	inc	esi
	mov	al,[esi]
	inc	ecx
	jne	l4

exit_l4:

	dec	esi
	mov	edi,reves

l5:

	cmp	ecx,0d
	je	exit_invierte
	mov	ah,[esi]
	mov	[edi],ah
	dec	esi
	inc	edi
	dec	ecx
	jne	l5

exit_invierte:

	ret
