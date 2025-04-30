# libgloss-dramfs

This is a minimalistic libgloss port for RISC-V that implements bare-metal I/O and filesystem support entirely in RAM, with zero host code.

See [bsg\_newlib\_dramfs](https://github.com/bespoke-silicon-group/bsg_newlib_dramfs) for a full explanation.

bsg\_newlib_\_dramfs initially required newlib patching. Instead, this libgloss porting structure was heavily inspired by [libgloss-htif](https://github.com/ucb-bar/libgloss-htif).

## Installation

    $ mkdir build
    $ cd build
    $ ../configure --prefix=${RISCV}/riscv64-unknown-elf --host=riscv64-unknown-elf
    $ make
    $ make install

**Note**: The installation prefix must be chosen such that the `libdir`
variable matches one of the library search paths of the RISC-V compiler.
For a typical cross-compiler toolchain, the prefix would generally be
the sysroot directory (`riscv64-unknown-elf-gcc -print-sysroot`).
Use the `--libdir` configure option to adjust the location if the final
directory component is not `/lib`.

## Porting

Porting libgloss-dramfs requires following four steps:
1. Implement `dramfs_exit(int)` (routine to exit the execution environment). 
2. Implement `dramfs_sendchar(char)` (routine to output non-file I/O (for debugging etc)).
3. (optional) Implement `dramfs_getchar(char)` (routine to input non-file I/O (for debugging etc)).
4. (optional) Create a C-array-based filesystem using the provided dramfs\_mklfs utility
5. (optional) Create a C-array-based argc/argv implementation

## Example Usage

    $ # runs an example with printf capabilities
    $ riscv64-unknown-elf-gcc -specs=dramfs.specs -o hello hello.c dramfs_intf_spike.c
    $ spike hello
        Hello world from printf
        argc: 1
        argv[0]: 0x8000dd58 panicroom

    $ # runs an example with printf and FS capabilities
    $ dramfs_mklfs 128 64 hello.txt > hello_lfs.c
    $ riscv64-unknown-elf-gcc -specs=dramfs.specs -o hello_fs hello.c dramfs_intf_spike.c hello_lfs.c
    $ spike hello_fs
		Hello world from printf

		Hello! This is Little FS!
		argc: 1
		argv[0]: 0x8000dd58 panicroom

    $ # runs an example with printf and argc/argv capabilities
    $ riscv64-unknown-elf-gcc -specs=dramfs.specs -o hello_argv hello.c dramfs_intf_spike.c args.c
    $ spike hello_fs
		Hello world from printf
		argc: 2
		argv[0]: 0x8000deb8 custom1
		argv[1]: 0x8000dec0 custom2

