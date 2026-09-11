jit.off()

-- local overlay = 'abst'      -- Save/Load Menu
-- local overlay = 'brf'       -- Briefing
-- local overlay = 'camera'    -- JPEG Photo Menu
-- local overlay = 'change'    -- Disc Change
-- local overlay = 'demosel'   -- Demo Theater
-- local overlay = 'ending'    -- Ending Demo (SCENE 28-1)
-- local overlay = 'endingr'   -- Ending Demo (SCENE 28-1) (RED)
-- local overlay = 'opening'   -- Opening Demo (SCENE 01-1)
-- local overlay = 'option'    -- Options Menu
-- local overlay = 'preope'    -- Previous Operations
-- local overlay = 'rank'      -- Ranking Screen
-- local overlay = 'roll'      -- Staff Roll
-- local overlay = 'select'    -- Debug Menu
-- local overlay = 'select1'   -- Debug Menu Stage Select (s00a-s04c)
-- local overlay = 'select2'   -- Debug Menu Stage Select (s05a-s09a)
-- local overlay = 'select3'   -- Debug Menu Stage Select (s10a-s14e)
-- local overlay = 'select4'   -- Debug Menu Stage Select (s15a-s20a)
-- local overlay = 'selectd'   -- Debug Menu Demo Select
-- local overlay = 'sound'     -- Debug Menu Sound Test
-- local overlay = 'title'     -- Title Screen

-- local overlay = 'd00a'      -- Loading Dock (Cutscene)
-- local overlay = 'd01a'      -- Heliport (Cutscene)
-- local overlay = 'd03a'      -- Holding Cell (Cutscene)
-- local overlay = 'd11c'      -- Communication Tower B (Cutscene)
-- local overlay = 'd16e'      -- Underground Base (Cutscene)
-- local overlay = 'd18a'      -- Supply Route (Cutscene)
-- local overlay = 'd18ar'     -- Supply Route (Cutscene) (RED)

-- local overlay = 's00a'      -- Loading Dock
-- local overlay = 's01a'      -- Heliport
-- local overlay = 's02a'      -- Tank Hangar
-- local overlay = 's02b'      -- Tank Hangar
-- local overlay = 's02c'      -- Tank Hangar (Before Contacting Meryl)
-- local overlay = 's02d'      -- Tank Hangar (After Contacting Meryl)
-- local overlay = 's02e'      -- Tank Hangar (After Torture)
-- local overlay = 's03a'      -- Holding Cell
-- local overlay = 's03ar'     -- Holding Cell (RED)
-- local overlay = 's03b'      -- Medical Room
-- local overlay = 's03c'      -- Medical Room
-- local overlay = 's03d'      -- Holding Cell
-- local overlay = 's03dr'     -- Holding Cell (RED)
-- local overlay = 's03e'      -- Holding Cell (vs. Soldiers)
-- local overlay = 's03er'     -- Holding Cell (vs. Soldiers) (RED)
-- local overlay = 's04a'      -- Armory
-- local overlay = 's04b'      -- Armory South (vs. Ocelot)
-- local overlay = 's04br'     -- Armory South (vs. Ocelot) (RED)
-- local overlay = 's04c'      -- Armory South
-- local overlay = 's05a'      -- Canyon
-- local overlay = 's06a'      -- Warhead Storage Building 1F
-- local overlay = 's07a'      -- Warhead Storage Building B1
-- local overlay = 's07b'      -- Commander's Room
-- local overlay = 's07br'     -- Commander's Room (RED)
-- local overlay = 's07c'      -- Warhead Storage Building B1
-- local overlay = 's07cr'     -- Warhead Storage Building B1 (RED)
-- local overlay = 's08a'      -- Warhead Storage Building B2
-- local overlay = 's08b'      -- Laboratory
-- local overlay = 's08br'     -- Laboratory (RED)
-- local overlay = 's08c'      -- Corridor
-- local overlay = 's08cr'     -- Corridor (RED)
-- local overlay = 's09a'      -- Caves
-- local overlay = 's09ar'     -- Caves (RED)
-- local overlay = 's10a'      -- Underground Passage
-- local overlay = 's10ar'     -- Underground Passage (RED)
-- local overlay = 's11a'      -- Communication Tower A
-- local overlay = 's11b'      -- Communication Tower Roof
-- local overlay = 's11c'      -- Communication Tower B
-- local overlay = 's11d'      -- Communication Tower A Wall
-- local overlay = 's11e'      -- Communication Tower B Elevator
-- local overlay = 's11g'      -- Communication Tower B Roof
-- local overlay = 's11h'      -- Communication Tower B Roof (vs. Hind D)
-- local overlay = 's11i'      -- Communication Tower Walkway
-- local overlay = 's12a'      -- Snowfield
-- local overlay = 's12b'      -- Snowfield (After vs. Sniper Wolf)
-- local overlay = 's12c'      -- Snowfield (After vs. Sniper Wolf)
-- local overlay = 's13a'      -- Blast Furnace
-- local overlay = 's14e'      -- Cargo Elevator
-- local overlay = 's15a'      -- Warehouse
-- local overlay = 's15b'      -- Warehouse North
-- local overlay = 's15c'      -- Warehouse
-- local overlay = 's16a'      -- Underground Base (1F)
local overlay = 's16b'      -- Underground Base (2F)
-- local overlay = 's16c'      -- Underground Base (3F)
-- local overlay = 's16d'      -- Underground Base (Control Room)
-- local overlay = 's17a'      -- Supply Route (vs. REX)
-- local overlay = 's17ar'     -- Supply Route (vs. REX) (RED)
-- local overlay = 's18a'      -- Supply Route (vs. Liquid)
-- local overlay = 's18ar'     -- Supply Route (vs. Liquid) (RED)
-- local overlay = 's19a'      -- Escape Route (Garage)
-- local overlay = 's19ar'     -- Escape Route (Garage) (RED)
-- local overlay = 's19b'      -- Escape Route (Tunnel)
-- local overlay = 's19br'     -- Escape Route (Tunnel) (RED)
-- local overlay = 's20a'      -- Ending Demo (SCENE 28-1)
-- local overlay = 's20ar'     -- Ending Demo (SCENE 28-1) (RED)

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
