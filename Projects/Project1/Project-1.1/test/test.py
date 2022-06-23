import json
import os
import sys

# {test_type : number of testcases}
TESTS = {'rtype':2, 'itype':2, 'stype':2, 'sbtype':1, 'utype':2, 'ujtype':1, 'full':1}

results = {}

def check_content(out_f, ref_f):
    out_lines = [l.strip() for l in out_f.readlines() if l.strip() != ""]
    ref_lines = [l.strip() for l in ref_f.readlines() if l.strip() != ""]
    if(len(out_lines) != len(ref_lines)):
        return 0
    for i in range(len(ref_lines)):
        if(out_lines[i] != ref_lines[i]):
            return 0
    return 1

def check_mem(mem_f):
    mem_lines = [l.strip() for l in mem_f.readlines() if l.strip() != ""]
    if mem_lines[-1].find("ERROR SUMMARY: 0 errors from 0 contexts") != -1:
        return 1  # correct
    else:
        return 0  # fails

mem_check = 1

for idx, name in enumerate(TESTS):
    for tidx in range(1, TESTS[name]+1):
        out_fname = f'out/{name}/output_{tidx}.s'
        ref_fname = f'ref/{name}/ref_{tidx}.s'
        mem_fname = f'out/{name}/memcheck_{tidx}.txt'
        try:
            with open(out_fname, 'r') as out_f,\
                 open(ref_fname, 'r') as ref_f, \
                 open(mem_fname, 'r') as mem_f:
                mem_check = mem_check & check_mem(mem_f)
                results[f'({name}){idx+1}-{tidx}'] = check_content(out_f, ref_f)
        except FileNotFoundError:
            results[f'({name}){idx+1}-{tidx}'] = 0
results[f'memory check'] = mem_check

print(json.dumps({'scores': results}, sort_keys=False, indent=1))
