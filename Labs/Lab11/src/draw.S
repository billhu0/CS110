.data
	hs:		.string "EricDiao"

.section .text
.globl 	draw
.type 	draw,	@function
draw:
		# YOUR CODE HERE
		addi 	sp,	sp,	-4
		sw 		ra,	0(sp)

		# draw a circle
		# LCD_DrawCircle(25, 40, 20, BLUE);
		li 		a0,	25
		li 		a1, 40
		li 		a2,	20
		li 		a3, 0x001F
		jal 	LCD_DrawCircle

		# draw a square
		# LCD_DrawRectangle(50, 20, 90, 60, RED);
		li		a0,	50
		li 		a1,	20
		li 		a2,	90
		li 		a3,	60
		li 		a4, 0xF800
		jal 	LCD_DrawRectangle

		# print a string
		# LCD_ShowString(hs, 95, 32, t0, GREEN);
		la 		t0,	hs  # a pointer to char* "EricDiao"
		li 		a0,	75
		li 		a1,	32
		mv 		a2,	t0
		li 		a3,	0x07E0
		jal 	LCD_ShowString

		# print a num
		# LCD_ShowNum(95, 48, 100, 3, RED);
		li		a0,	95
		li 		a1,	48
		li 		a2,	100
		li 		a3,	3
		li 		a4, 0xF800
		jal 	LCD_ShowNum

		lw 		ra,	0(sp)
		addi 	sp,	sp,	4
		ret 
