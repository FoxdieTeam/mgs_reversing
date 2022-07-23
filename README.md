What, what is this?

This project aims to completely reverse engineer Metal Gear Solid for PlayStation back to C source code which when compiled produces the same assembly code.

How to build.

1.  Install python 3 if it isn't and make sure it's in your PATH
2.  Clone down the PSYQ SDK repo from: https://github.com/FoxdieTeam/psyq_sdk.git
3.  Clone down this repo.
4.  Open a terminal and cd into the build directory.
5.  Issue the command "pip install -r requirements.txt"
6.  Issue the command "python build.py --psyq_path=YourPath" where 'YourPath' is the location of your cloned psyq_sdk depot.
    - Alternatively you can add "PSYQ_SDK" in your environment variables before invoking "python build.py".
7.  At the end you should see a message confirming that the built binaries hash matches the original games binary hash.

How to decompile a function.

Using IDA or Ghidra disassemble the original game binary, or use one that you compiled yourself provided that the output was OK. Now choose a .s file from the asm directory where that function isn’t part of the “mts” system and also isn’t part of “psyq”.
Given the address of the function go to this location in your reversing tool. Delete the .s file and create a .c file. In the .c file write a function with the same name as the file and build. The build will not be OK as your empty function will no longer build a matching binary.
Now comes the hard part, implement the function such that it matches the functionality of the assembly and build again. Repeat this until your build is OK – i.e your C code is functionally the same and produces exactly the same assembly as the original function.

Help I am totally stuck?

Join our discord here https://discord.gg/tTvhQ8w and ask for help in #metal_gear_dev
