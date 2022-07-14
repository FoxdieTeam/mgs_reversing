#import _mgsi.map
#@category _MGS

code_start = 0x800148B8
code_end = 0x8009D2DB

f = open('../../obj/_mgsi.map'
lines = f.readlines()

for line in lines:
  pieces = line.split()
  if (len(pieces) != 2):
    continue
  
  name = pieces[1]
  if (name.startswith('_')):
    continue
  
  address = toAddr(pieces[0])
  addr = int(pieces[0], 16)
  
  if addr >= code_start and addr < code_end:
    print('func', address, name)
    func = getFunctionAt(address)

    if func:
      createLabel(address, name, True)
    else:
      createFunction(address, name)
    
    disassemble(address)
  else:
    print('label', address, name)
    createLabel(address, name, False)

disassemble(toAddr(0x80081c68)) # fix a weird branch target
