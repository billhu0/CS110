start: lui x5, 8
sw x12,12(x13)
jal x1, end
srli x10, x10, 1
jal x0, start
end: addi x3, x3, 30
