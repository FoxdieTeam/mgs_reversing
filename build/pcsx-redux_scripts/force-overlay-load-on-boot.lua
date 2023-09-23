jit.off()

if loader_bp == nil then                                                                                                    
    loader_bp = PCSX.addBreakpoint(0x800236E0, 'Exec', 4, 'loader', function()                                              
       local regs = PCSX.getRegisters()                                                                                    
       local addr = bit.band(regs.GPR.n.a0, 0x1fffff)     
       local mem = PCSX.getMemPtr()
       local ptr = ffi.cast('uint8_t*', mem + addr)                                                                        
       ptr[0] = string.byte('c');                                                                                          
       ptr[1] = string.byte('h');                                                                                          
       ptr[2] = string.byte('a');                                                                                          
       ptr[3] = string.byte('n');                                                                                          
       ptr[4] = string.byte('g');                                                                                          
       ptr[5] = string.byte('e');                                                                                          
       ptr[6] = 0;                                                                                                         
    end)                                                                                                                    
end       
