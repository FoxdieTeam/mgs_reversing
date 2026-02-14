#@category _MGS
from ghidra.app.decompiler import DecompInterface

decomp = DecompInterface()
decomp.openProgram(currentProgram)

fm = currentProgram.getFunctionManager()

declarations = []

root_dir = r'/home/thomas/psx/re/mgs/wanted_mgs_reverse_tools/'

for func in fm.getFunctions(toAddr(0x800148B8), True):
    decompiled_func = decomp.decompileFunction(func, 1000, monitor).getDecompiledFunction()
    
    declarations.append(decompiled_func.getSignature() + '\n')
    
    with open(root_dir + 'ghidra_export/functions/' + func.getName() + '.c', 'w') as file:
        file.write(decompiled_func.getC().replace('\r\r','\r'))

with open(root_dir + 'converter/funcs_names/ghidra_funcs.txt', 'w') as file:
    file.writelines(declarations)
