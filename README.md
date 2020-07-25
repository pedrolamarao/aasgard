Date: 2020-07-24

# summary

Welcome to the Aasgard project!

Aasgard is a collection of components for programming the bare metal.

It is designed for integration with state of the art tools.

# index

0. summary
1. prepare
2. assemble
3. check
4. use
5. architecture
6. references

# prepare

Aasgard is currently built using custom cross tools installed to prefix `${projectDir}/tools`.
The build system is wired to use the tools at this prefix.

To acquire the necessary sources, run `tools/src.sh`.
This script requires `wget`.

Next, you must install tool dependencies.
For Fedora 32, run `tools/fedora.sh`.
For Debian, run `tools/debian.sh`.
These scripts we written based on experience.
If the next step fails, maybe something is missing.

To build the tools, run `tools/build.sh`.

- GNU Binutils target `i386-pc-elf`
- GNU Binutils target `x86_64-pc-elf`
- GNU GCC languages C, C++ target `i386-pc-elf`
- GNU GCC languages C, C++ target `x86_64-pc-elf`
- GNU GDB target `i386-pc-elf`
- GNU GDB target `x86_64-pc-elf`
- GNU GRUB target `i386-pc`
- GNU GRUB target ...
- QEMU

# assemble

Aasgard's build system is based on Gradle exended with custom plugins.
This system requires a JDK version 11.
JRE is not enough to compile the custom plugins.

To assemble development artifacts, do `./gradlew assemble`

To clean all generated artifacts, do `./gradlew clean`

# check

Aasgard is verified by a technique orchestrating QEMU and GDB to watch for "asserts".

To check development artifacts, do `./gradlew check`

# use

Aasgard is reusable as Gradle subprojects.

Each component is a maven-like module.

To reuse one of the components, simply add a dependency on it:

```gradle
dependencies {
    implementation project(':multiboot2')
}
```

# architecture

The collection includes the following components:

* [acpi](acpi/README.md)
* [multiboot2](multiboot2/README.md)
* [pc](pc/README.md)
* [x86](x86/README.md)

# references

_TODO_
