# What, what is this?

This project aims to completely reverse engineer *Metal Gear Solid* for PlayStation back to C source code which when compiled produces the same assembly code.

# How to build

1.  Install Python 3 if you haven't and make sure it's in your PATH.
2.  Clone down the PsyQ SDK repo from: https://github.com/FoxdieTeam/psyq_sdk.git
    ⚠️ Make sure your path isn't too long, PsyQ can't deal with paths longer than 255 characters.
3.  Clone down this repo.
4.  Open a terminal and `cd` into the build directory.
5.  Issue the command `pip install -r requirements.txt`.
6.  Issue the command `python build.py --psyq_path=YourPath` where `YourPath` is the location of your cloned psyq_sdk depot.
    - Alternatively you can add `PSYQ_SDK` to your environment variables before invoking `python build.py`.
7.  At the end you should see a message confirming that the built binary's hash matches the original game's binary's hash. If your code caused the compiler to emit warnings, try to fix them without breaking the match.

# How to decompile a function

Using IDA or Ghidra (with the [ghidra_psx_ldr extension](https://github.com/lab313ru/ghidra_psx_ldr/)) disassemble the original game binary (SLPM-86247), or use one that you compiled yourself provided that the output was OK. Now choose a .s file from the asm directory where that function isn’t part of `psyq`.

Given the address of the function go to this location in your reversing tool. Delete the .s file and search for a .c file which has a `#pragma INCLUDE_ASM()` directive pointing to the former .s file; if none exists, create a .c file with the name of the function and open it. Now write an empty C function that has the same name as the former assembly function as well as a suitable signature; when you re-execute `python build.py`, the build will not be OK as your empty function will no longer build a matching binary.

Now comes the hard part: implement the function such that it matches the functionality of the assembly and build again. Repeat this until your build is OK – ie your C code is functionally the same and produces exactly the same assembly as the original function.

Iterative building is currently unreliable and it is highly recommended to run `make clean && python build.py` to be certain that your binary is truly a match.

# Help, I am totally stuck?

Join [our Discord](https://discord.gg/tTvhQ8w) and ask for help in `#metal_gear_dev`.

There are various Ghidra scripts in `build/ghidra_scripts/` to help with decompilation:

- `import_map.py`: when you have produced a matching build, this imports the symbols from the map file into Ghidra;
- `update_data.py`: make sure to read the instructions to this script, which updates data in accordance with declared data types provided they have been imported from header files;
- `update_functions.py`: updates function return types and parameters according to the declarations of matched functions.

It is highly recommended to re-run auto-analysis whenever you have executed these scripts.

We make extensive use of [decomp.me](https://decomp.me/), which has a *Metal Gear Solid* preset, to help match functions; before working on a function, search for it on the website and if you don't find it, go to the `build` folder and run `python decompme_asm.py [path to .s file]` to have the assembly instructions in your clipboard ready to paste into a new decomp.me scratch.
