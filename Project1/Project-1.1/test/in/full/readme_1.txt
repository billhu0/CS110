multiply:
  add  t0, zero, zero
  addi a1, a1, -1
accumulate:
  add  t0, t0, a0
  addi a1, a1, -1
  bge  a1, zero, accumulate
  add  a0, zero, t0
  ret
