# WinBGI

## Instruction to install graphics.h in DevC++.

  - You must have 3 files.
            - graphics.h
            - libbgi.a
            - test.cpp
            inside wBGi folder
  - Open DevC++ installed directory By Right Clicking the shortcut and click open file location.
  - Inside DevC++ installed directory open MinGW64 Folder.
  - copy graphics.h to include Folder which is inside MinGW64.
  - Again copy libbgi.a to lib Folder which is inside MinGW64.
  - now open test.cpp in DevC++.
  - in the menubar go to tools->Compiler Options.
  - In the Genaral Tab make sure the button saying "Add the following command when calling linker." is checked.
  - Inside the box just below it add the following command "-lbgi  -lgdi32" without quotes.
  - Click OK
  - Now Compile and Run the wBGI\test.c program.
