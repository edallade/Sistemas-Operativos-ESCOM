
segment .data


salto db 0Ah
num db 30h
;ref db 3Ah  variable eliminada pues aunque no se
            ;use si no se pone comentada el programa no
            ;funciona  
segment .text
global _start

_start:


	mov 	edx,1
loop1:

	mov	ecx,num
	mov	ebx,1
	mov	eax,4
	int	0x80

	mov	ecx,salto
	mov	ebx,1
	mov	eax,4
	int	0x80



	mov	ecx,[num]
	inc	ecx
	mov	[num],ecx
	cmp     ecx,3Ah
	jne	loop1

	mov	eax,1
	int 	0x80
