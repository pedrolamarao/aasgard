Date: 2020-02-27

# summary

The `ia32-multiboot2` component supports the Multiboot specification version 2 binding for IA32.

This component enables immediate transitions to a well defined C `main` function.

# use

## `main`

This component receives control from the boot loader and, as soon as possible, calls the following function:

```c++
extern "C"
[[gnu::fastcall]]
void main (uint32_t magic, void* mbi);
```

where `mbi` is in fact the address for the Multiboot response.

For more information, see documentation for the `multiboot2` component.

# architecture

This component contains IA32 assembly code in `start.s`.

This file defines the default ELF entry point `_start`.

The entry point does the smallest amount of configuration required to call an external `main`.

# references

* "I386 machine state", _in_ "The Multiboot Specification", version 2.0 [link](https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#I386-machine-state)
