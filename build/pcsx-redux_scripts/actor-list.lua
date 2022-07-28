---@diagnostic disable:undefined-global
---@diagnostic disable:lowercase-global

-- actor list viewer with buttons to kill and freeze actors
-- https://i.imgur.com/f4XEW3Y.png
-- open Lua Console to see spawned actors and their sizes

-- globals (persist reload)
if breakpoints ~= nil then
    print('removing existing breakpoints')
    for _, bp in pairs(breakpoints) do
        bp:remove()
    end
end
breakpoints = {}
actor_sizes = {}

--

local mem = PCSX.getMemPtr()

jit.off() -- shit's buggy and crashes a lot

local fmt = string.format

local function u32(addr)
    addr = bit.band(addr, 0x1fffff)
    local ptr = ffi.cast('uint32_t*', mem + addr)
    return ptr[0]
end

local function wu32(addr, value)
    addr = bit.band(addr, 0x1fffff)
    local ptr = ffi.cast('uint32_t*', mem + addr)
    ptr[0] = value
end

local function u8(addr)
    addr = bit.band(addr, 0x1fffff)
    local ptr = ffi.cast('uint8_t*', mem + addr)
    return ptr[0]
end

local function cstr(addr)
    local str = ''
    local i = 0
    repeat
        local byte = u8(addr + i)
        if byte ~= 0 then
            str = str .. string.char(byte)
        end
        i = i + 1
    until byte == 0
    return str
end

local actorlist_base = 0x800acc18
local actor_size = 4 * 8
local actorlist_struct_size = (actor_size * 2) + 2 + 2
local update_off = 4 + 4
local next_off = 4
local name_off = update_off + 12

local function actor_list()
    local list_off = 0
    imgui.Columns(9)
    for list_idx = 0, 9-1 do
        list_off = (actorlist_struct_size * list_idx)
        local actorlist = actorlist_base + list_off
        if imgui.Button(fmt("ActorList[%d] %X", list_idx, actorlist)) then
            PCSX.GUI.jumpToMemory(actorlist)
        end
        imgui.NewLine()
        local actor = u32(actorlist_base + list_off + next_off)
        repeat
            local update_fn = u32(actor + update_off)
            if update_fn ~= 0 then
                local name_ptr = u32(actor + name_off)
                local name = cstr(name_ptr)

                imgui.PushID(actor)
                if imgui.Button('K') then
                    -- PCSX.GUI.jumpToMemory(actor + update_off)
                    wu32(actor + update_off, 0x80015164) -- kill
                end
                imgui.SameLine()
                if imgui.Button('F') then
                    -- PCSX.GUI.jumpToMemory(actor + update_off)
                    wu32(actor + update_off, 0x80053b80) -- nullsub
                end
                imgui.SameLine()
                if imgui.Button(fmt('%X %s', actor, name)) then
                    PCSX.GUI.jumpToMemory(actor)
                end
                imgui.PopID(actor)
            end

            actor = u32(actor + next_off)
        until actor == 0

        imgui.NextColumn()
    end
end

function DrawImguiFrame()
    -- for x, y in pairs(actor_sizes) do
    --     print(fmt("%X %X", x, y))
    -- end
    actor_sizes = {} -- reset every frame

    show = imgui.Begin('ActorList', true)
    if not show then imgui.End() return end
    actor_list()
    imgui.End()
end

-- GV_NewActor_800150E4
local new_actor_bp = PCSX.addBreakpoint(0x80015114, 'Exec', 4, 'GV_NewActor_800150E4', function()
    local regs = PCSX.getRegisters()
    local actor = regs.GPR.n.a0
    local size = regs.GPR.n.s1
    actor_sizes[actor] = size
    -- print(fmt('GV_NewActor %X %X', actor, size))
end)
breakpoints[new_actor_bp] = new_actor_bp

-- GV_SetNamedActor_8001514C
local named_actor_bp = PCSX.addBreakpoint(0x8001514c, 'Exec', 4, 'GV_SetNamedActor_8001514C', function()
    local regs = PCSX.getRegisters()
    local actor = regs.GPR.n.a0
    local name_ptr = regs.GPR.n.a3

    local size = actor_sizes[actor]
    if size ~= nil then
        actor_sizes[actor] = size
        local name = cstr(name_ptr)
        if name ~= 'anime.c' and name ~= 'asiato.c' then -- spammy
            print(fmt('GV_SetNamedActor %X %s size 0x%X', actor, name, size))
        end
    end
end)
breakpoints[named_actor_bp] = named_actor_bp
