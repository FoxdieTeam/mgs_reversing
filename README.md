# mgs_reversing

This project aims to completely reverse engineer *Metal Gear Solid Integral* for PlayStation back to C source code which when compiled produces the same assembly code.

At this moment `SLPM_862.47`/`SLPM_862.48` main executables are 100% decompiled. However, even though this is a substantial milestone, a significant amount of work
is still left to decompile [overlays](#Overlays), clean up already decompiled code and make it all shiftable.

The repository builds or aims to build the following artifacts:

### Main executables

<table>
    <tbody>
        <tr>
            <td colspan=2 align=center><b><code>SLPM_862.47</code> (main executable)</b></td>
        </tr>
        <tr>
            <td><b>Status</b></td>
            <td><b>100% decompiled!</b> The next goals for this artifact are to clean up the decompiled code, find cleaner matches and make it shiftable.</td>
        </tr>
        <tr>
            <td><b>SHA256</b></td>
            <td><code>4b8252b65953a02021486406cfcdca1c7670d1d1a8f3cf6e750ef6e360dc3a2f</code></td>
        </tr>
        <tr>
            <td><b>Building</b></td>
            <td><code>python build.py</code></td>
        </tr>
        <tr>
            <td colspan=2 align=center><b><code>SLPM_862.48</code> (main executable)</b></td>
        </tr>
        <tr>
            <td><b>Status</b></td>
            <td rowspan=3><b>100% decompiled!</b> Identical to <code>SLPM_862.47</code> (main executable).</td>
        </tr>
        <tr>
            <td><b>SHA256</b></td>
        </tr>
        <tr>
            <td><b>Building</b></td>
        </tr>
        <tr>
            <td colspan=2 align=center><b><code>SLPM_862.49</code> (main executable)</b></td>
        </tr>
        <tr>
            <td><b>Status</b></td>
            <td>The project builds a matching executable. <code>chara/snake_vr/sna_init.c</code> (a variant of Snake from <code>SLPM_862.47</code> main executable) is the only file left to decompile.</td>
        </tr>
        <tr>
            <td><b>SHA256</b></td>
            <td><code>c370f8e41ec8fb78238bfe2ddbfc25a6d37ec8f0972c86ebfde075ecd4ee8dca</code></td>
        </tr>
        <tr>
            <td><b>Building</b></td>
            <td><code>python build.py && python build.py --variant=vr_exe</code></td>
        </tr>
    </tbody>
</table>

### Overlays

*Metal Gear Solid Integral* dynamically loads additional per-stage executable code that is required to play a particular stage of the game. The main executable contains the game engine, as well as the most common actors used throughout the stages.

<table>
    <tbody>
        <tr>
            <td colspan=2 align=center><b>Overlays on <code>SLPM-86247</code></b></td>
        </tr>
        <tr>
            <td><b>Status</b></td>
            <td>Work in progress. Several overlays (out of 92) are fully decompiled.</td>
        </tr>
        <tr>
            <td colspan=2 align=center><b>Overlays on <code>SLPM-86248</code></b></td>
        </tr>
        <tr>
            <td><b>Status</b></td>
            <td>Identical to <code>SLPM-86247</code> overlays.</td>
        </tr>
        <tr>
            <td colspan=2 align=center><b>Overlays on <code>SLPM-86249</code></b></td>
        </tr>
        <tr>
            <td><b>Status</b></td>
            <td>Work on it not yet started.</td>
        </tr>
    </tbody>
</table>

## How to build

1.  Install Python 3 if you haven't and make sure it's in your PATH.
2.  Clone down the PsyQ SDK repo from: https://github.com/FoxdieTeam/psyq_sdk.git
3.  Clone down this repo.
4.  Open a terminal and `cd` into the build directory.
5.  Issue the command `pip install -r requirements.txt`.
6.  Issue the command `python build.py --psyq_path=YourPath` where `YourPath` is the location of your cloned psyq_sdk depot.
    - Alternatively you can add `PSYQ_SDK` to your environment variables before invoking `python build.py`.
7.  At the end you should see a message confirming that the built binary's hash matches the original game's binary's hash. If your code caused the compiler to emit warnings, try to fix them without breaking the match.

## How to decompile a function

**Now that the work is moving onto overlays, this section is no longer up to date. Please join [our Discord](https://discord.gg/tTvhQ8w) and ask for help in `#metal_gear_dev`.**

Using IDA or Ghidra (with the [ghidra_psx_ldr extension](https://github.com/lab313ru/ghidra_psx_ldr/)) disassemble the original game binary (SLPM-86247), or use one that you compiled yourself provided that the output was OK. Now choose a .s file from the asm directory where that function isn’t part of `psyq`.

Given the address of the function go to this location in your reversing tool. Delete the .s file and search for a .c file which has a `#pragma INCLUDE_ASM()` directive pointing to the former .s file; if none exists, create a .c file with the name of the function and open it. Now write an empty C function that has the same name as the former assembly function as well as a suitable signature; when you re-execute `python build.py`, the build will not be OK as your empty function will no longer build a matching binary.

Now comes the hard part: implement the function such that it matches the functionality of the assembly and build again. Repeat this until your build is OK – ie your C code is functionally the same and produces exactly the same assembly as the original function.

Iterative building is currently unreliable and it is highly recommended to run `python clean.py && python build.py` to be certain that your binary is truly a match.

## Help, I am totally stuck?

Join [our Discord](https://discord.gg/tTvhQ8w) and ask for help in `#metal_gear_dev`.

There are various Ghidra scripts in `build/ghidra_scripts/` to help with decompilation:

- `import_map.py`: when you have produced a matching build, this imports the symbols from the map file into Ghidra;
- `update_data.py`: make sure to read the instructions to this script, which updates data in accordance with declared data types provided they have been imported from header files;
- `update_functions.py`: updates function return types and parameters according to the declarations of matched functions.

It is highly recommended to re-run auto-analysis whenever you have executed these scripts.

We make extensive use of [decomp.me](https://decomp.me/), which has a *Metal Gear Solid* preset, to help match functions; before working on a function, search for it on the website and if you don't find it, go to the `build` folder and run `python decompme_asm.py [path to .s file]` to have the assembly instructions in your clipboard ready to paste into a new decomp.me scratch.
