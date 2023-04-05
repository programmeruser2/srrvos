.section .text
.global _start
_start:
	li s1, 0x10000000 
  li s2, 0x61       
	sb s2, 0(s1)
	.loop: j .loop
