# Valgrind notes
NB: This note does not aim at providing a comprehensive intoroduction to valgrind,
rather it is a collection of useful topics and cues to help you retain memory of the valgrind manual, quick start guide, and FAQ.
## Quick start guide
1) Compile like this: `g++ -g -O0 [-O1] main.cpp -o main.out`
`-g` tells g++ to include debugging information so that valgrind can show **exact line numbers** in its output.
`-O0` disables all optimizations so that *main.out* doesn't take unexpected detours during execution. If you can't tolerate the speed loss caused by this option, use `-01` instead. 
2) Run under valgrind: `valgrind --leak-check=yes ./main.cpp arg1 arg2`
`--leak-check=yes` enables the detailed memory leak detector.
3) Tips & other flags:
`--num-callers` to make the stack trace bigger.
Read memcheck's output *from the bottom up*.
Memcheck doesn't do bounds checking on *global or stack arrays*.
## Manual
### The Valgrind core
1) `--tool`indicates which valgrind tool to run. The default is memcheck.
2) What valgrind does when running your program:
- Valgrind takes control of your program before it starts: debugging information is read from the executable and associated libraries.
- Your program is then run on a synthetic CPU provided by the Valgrind core. The core hands new code to the selected tool. The tool adds its own instrumentation code to this and hands the result back to the core, which coordinates the continued execution of this instrumented code.
- Valgrind simulates every single instruction your program executes. Because of this, the active tool checks, or profiles, not only the code in your application but also in all supporting dynamically-linked libraries, including the C library, graphical libraries, and so on.
3) Valgrind may detect errors in system libraries. To suppress them:
`--gen-suppressions=yes`  print suppressions for each error.
4) `-fno-inline` ease seeing the function-call chain.
5) Commentary:
By default, valgrind sends its messages to stderr (i.e. default file descriptor is 2).
`--log-file=filename` send commentary to filename
6) Core command-line options:
`-h` help on options for both core and selected tool.
`-v` be more verbose, use twice to add even more intel.
`--vgdb=<no|yes|full> [default: yes]` allow gdb to debug your program under valgrind. **SEE ADVANCED TOPICS.**
`--time-stamp=<yes|no> [default: no]` add timestamps to each message.
`--fullpath-after=<string> [default: don't show source paths]` show full paths to source files (useful in large projects).
7) Config files:
File `~/.valgrindrc` and the env. variable `$VALGRIND_OPTS` contain options that will be passed to valgrind **before** command-line ones.
`--memcheck:leak-check=yes` example line in files.
### Advanced topics
TODO: finish this section.
### Memcheck
1) `[--read-var-info]` Memcheck will give a more detailed description of any illegal address.
2) Your program can copy around junk (uninitialised) data as much as it likes. 
Memcheck observes this and keeps track of the data, but does not complain. 
A complaint is issued only when your program attempts to make use of uninitialised data in a way that might affect your program's externally-visible behaviour (e.g. print it).
`--track-origins=yes` will give you extra information about the origin of uninitialised values.
3) On Linux apparently it doesn't matter if you do mix *free,* *delete*, and *delete[]* up.
On other platforms, however, the program may crash.
4) Leak kinds:
"Still reachable". There's a pointer remaining to an unfreed heap block. Could've been freed by the programmer but arguably not a problem at all. *Not shown* by default.
"Definitely lost". Fix me. *Shown* by default.
"Indirectly lost". Pointers to blocks are lost (e.g. the root node of a binary tree is lost so all children are indirectly lost). Fix "definitely lost" errors to fix these. *Not shown* by default.
"Possibly lost". There's a pointer pointing to the middle of the block. *Shown* by default.
`--leak-check=full` to show more info.
5) Checking machinery:
Every bit (literally) of data processed, stored and handled by the real CPU has, in the synthetic CPU, an associated "valid-value" bit (aka **V bit**), which says whether or not the accompanying bit has a **legitimate value**.
Copying values around **does not** cause Memcheck to check for, or report on, errors. However, when a value is used in a way which might conceivably affect your program's externally-visible behaviour, the associated V bits are immediately checked. If any of these indicate that the value is undefined (even partially), an error is reported (e.g. ifs on uninitialized values).
In addition, all bytes in memory, but not in the CPU, have an associated valid-address bit (aka **A bit**). This indicates whether or not the program can **legitimately read or write** that location. When memory is read or written, the relevant A bits are consulted. If they indicate an invalid address, Memcheck emits an error.
> Each byte in memory has 8 associated V (valid-value) bits, saying whether or not the byte has a defined value, and a single A (valid-address) bit.

