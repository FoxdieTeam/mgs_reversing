#@category _MGS
import os
from ghidra.program.model.listing import Function, ParameterImpl, ReturnParameterImpl, Variable, VariableStorage
from ghidra.program.model.symbol import SourceType
from ghidra.program.model.data import PointerDataType

dtm = currentProgram.getDataTypeManager()

def find_data_type(typename):
    data_types = []
    dtm.findDataTypes(typename, data_types)
    if (len(data_types) == 0):
        if typename.endswith('*'):
            return PointerDataType(find_data_type(typename[:-1].rstrip()))
        else:
            return None
    data_type = data_types[0]
    for dt in data_types:
        if dt.getName() == typename:
            data_type = dt
            break
    return data_type

root_dir = os.path.realpath(os.path.join(os.path.dirname(__file__), '../../'))

symbol_address_map = { }
with open(root_dir + '/obj/asm.map') as mapfile:
    lines = mapfile.readlines()
    for line in lines:
        pieces = line.split()
        if len(pieces) != 2:
            continue
        
        symbol = pieces[1]
        if symbol.startswith('_'):
            continue
            
        symbol_address_map[symbol] = pieces[0]
        
analyzed_funcs = []

with open(root_dir + '/build/ghidra_scripts/update_functions.log', 'w') as logfile:
    for root, subdirs, files in os.walk(root_dir + '/source'):
        for filename in files:
            filepath = os.path.join(root, filename)
            
            with open(filepath, 'r') as f:
                lines = f.readlines()
                for line in lines:

                    log_output = []

                    pieces = line.split()
                    if len(pieces) < 2:
                        continue
                        
                    pieces_base_index = 0
                    if pieces[0].partition('(')[0] in symbol_address_map:
                        continue
                    if pieces[0] == '#define' or pieces[0] == 'return':
                        continue
                    if pieces[0] == 'static' or pieces[0] == 'const':
                        pieces_base_index += 1
                    if pieces[1] == 'static' or pieces[1] == 'const':
                        pieces_base_index += 1
                    if pieces[pieces_base_index + 1].__contains__('SECTION') or not pieces[pieces_base_index + 1].__contains__('('):
                        continue
                    
                    func_type = pieces[pieces_base_index]
                    func_name = pieces[pieces_base_index + 1].partition('(')[0]
                    
                    if func_name.startswith('*'):
                        ptr_count = func_name.count('*')
                        assert ptr_count < 3
                        func_name = func_name.lstrip('*')
                        func_type = func_type.ljust(ptr_count + len(func_type), '*')
                    
                    if func_name in symbol_address_map:
                        if func_name in analyzed_funcs:
                            continue
                        else:
                            analyzed_funcs.append(func_name)
                        func_address = toAddr(symbol_address_map[func_name])
                        func = getFunctionAt(func_address)
                        assert func
                        
                        returnType = find_data_type(func_type)
                        
                        log_output.append('Ghidra old: \t' + func.getPrototypeString(True, False) + '\n')
                        log_output.append('Source code: \t' + line)
                            
                        if not line.__contains__(')'):
                            #@todo: deal with this case.
                            continue

                        params = line[line.find('(') + 1:line.rfind(')')]
                        if len(params.split()) < 2:
                            continue

                        updated_ghidra_params = []

                        parampieces = params.split(',')
                        for i in range(0, len(parampieces)): # Ignore missing params for now
                            param = parampieces[i].split()
                            if (param[0] == 'unsigned'):
                                param.pop(0)
                                param[0] = 'u' + param[0]
                            elif (param[0] == 'struct') or param[0] == 'const':
                                param.pop(0)
                            param_type = param[0]
                            param_name = param[-1]
                            
                            if param_name.startswith('(*'):
                                param_type = 'f *'
                            elif param_name.startswith('*'):
                                ptr_count = param_name.count('*')
                                assert ptr_count < 3
                                param_name = param_name.lstrip('*')
                                param_type += ptr_count * ' *'
                                
                            data_type = find_data_type(param_type)

                            if param_name == param_type:
                                param_name += '_' + str(i)

                            print('updating function: ' + func_name + '; parameter number: ' + str(i))
                            updated_ghidra_params.append(ParameterImpl(param_name, data_type, currentProgram))

                        func.updateFunction(None, ReturnParameterImpl(returnType, currentProgram), Function.FunctionUpdateType.DYNAMIC_STORAGE_ALL_PARAMS, True, SourceType.IMPORTED, updated_ghidra_params)

                        log_output.append('Ghidra new: \t' + func.getPrototypeString(True, False) + '\n')
                        log_output.append('******************************************************\n')
                        for log_line in log_output:
                            logfile.write(log_line)
