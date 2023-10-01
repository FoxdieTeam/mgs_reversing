jit.off()

-- local overlay = 'abst'    -- load save from memcard
-- local overlay = 'brf'     -- briefing
-- local overlay = 'camera'  -- load jpeg from memcard
-- local overlay = 'change'  -- disc change
-- local overlay = 'demosel' -- demo theater
-- local overlay = 'ending'
-- local overlay = 'endingr'
-- local overlay = 'opening' -- intro 'fmv'
-- local overlay = 'option'  -- options
-- local overlay = 'preope'  -- previous operations
-- local overlay = 'rank'    -- end game rank
-- local overlay = 'roll'    -- credits
-- local overlay = 'select'  -- debug menu
-- local overlay = 'select1' -- debug menu stage select
-- local overlay = 'select2' -- debug menu stage select S05A-S09A
-- local overlay = 'select3' -- debug menu stage select S10A-S14E1
-- local overlay = 'select4' -- debug menu stage select S15A-S20A
-- local overlay = 'selectd' -- debug menu demo select
-- local overlay = 'sound'   -- debug menu sound test
-- local overlay = 'title'   -- konami logo and title screen

-- local overlay = 'd00a'    -- docks cutscene
-- local overlay = 'd01a'    -- helipad cutscene
-- local overlay = 'd03a'    -- "s003c0.dmo"
-- local overlay = 'd11c'    -- elevator cutscene
-- local overlay = 'd16e'    -- rex cutscene
-- local overlay = 'd18a'    -- end tunnel cutscene?
-- local overlay = 'd18ar'   -- same as above? otacon/meryl versions?

-- local overlay = 's00a'    -- docks
-- local overlay = 's01a'    -- heliport
-- local overlay = 's02a'
-- local overlay = 's02b'
-- local overlay = 's02c'
-- local overlay = 's02d'
-- local overlay = 's02e'
-- local overlay = 's03a'
-- local overlay = 's03ar'
-- local overlay = 's03b'
-- local overlay = 's03c'
-- local overlay = 's03d'
-- local overlay = 's03dr'
-- local overlay = 's03e'
-- local overlay = 's03er'
-- local overlay = 's04a'
-- local overlay = 's04b'
-- local overlay = 's04br'
-- local overlay = 's04c'
-- local overlay = 's05a'
-- local overlay = 's06a'
-- local overlay = 's07a'
-- local overlay = 's07b'
-- local overlay = 's07br'
-- local overlay = 's07c'
-- local overlay = 's07cr'
-- local overlay = 's08a'
-- local overlay = 's08b'
-- local overlay = 's08br'
-- local overlay = 's08c'
-- local overlay = 's08cr'
-- local overlay = 's09a'
-- local overlay = 's09ar'
-- local overlay = 's10a'
-- local overlay = 's10ar'
-- local overlay = 's11a'
-- local overlay = 's11b'
-- local overlay = 's11c'
-- local overlay = 's11d'
-- local overlay = 's11e'
-- local overlay = 's11g'
-- local overlay = 's11h'
-- local overlay = 's11i'
-- local overlay = 's12a'
-- local overlay = 's12b'
-- local overlay = 's12c'
-- local overlay = 's13a'
-- local overlay = 's14e'
-- local overlay = 's15a'
-- local overlay = 's15b'
-- local overlay = 's15c'
-- local overlay = 's16a'
local overlay = 's16b'    -- smallest playable stage
-- local overlay = 's16c'
-- local overlay = 's16d'
-- local overlay = 's17a'
-- local overlay = 's17ar'
-- local overlay = 's18a'
-- local overlay = 's18ar'
-- local overlay = 's19a'
-- local overlay = 's19ar'
-- local overlay = 's19b'
-- local overlay = 's19br'
-- local overlay = 's20a'
-- local overlay = 's20ar'

local mem = PCSX.getMemPtr()

local function u8(addr)
    addr = bit.band(addr, 0x1fffff)
    local ptr = ffi.cast('uint8_t*', mem + addr)
    return ptr[0]
end

local function c_str(addr)
    local str = ''
    if str_ptr ~= 0 then
        local i = 0
        repeat
            local byte = u8(addr + i)
            if byte ~= 0 then
                str = str .. string.char(byte)
            end
            i = i + 1
        until byte == 0
    end
    return str
end

if loader_bp == nil then                                                                                                    
    loader_bp = PCSX.addBreakpoint(0x8002E460, 'Exec', 4, 'loader', function()
       local regs = PCSX.getRegisters()                                                                                    
       local addr = bit.band(regs.GPR.n.a0, 0x1fffff)     
       local mem = PCSX.getMemPtr()
       local name =  c_str(regs.GPR.n.a0)
       if name == 'title' then
            local ptr = ffi.cast('uint8_t*', mem + addr)
            local i = 0
            for c in overlay:gmatch('.') do
                ptr[i] = string.byte(c)
                i = i + 1
            end
            ptr[i] = 0
            print('forcing load of overlay:', overlay)
       end
    end)                                                                                                                    
end       
