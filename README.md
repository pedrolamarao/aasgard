Date: 2020-01-31

# summary

Welcome to the Aasgard project!

Aasgard is a collection of components for programming the bare metal.

It is designed for integration with state of the art tools.

Try: `./gradlew check`

# index

0. summary
1. assemble
2. check
3. use
4. architecture
5. references

# build

To assemble development artifacts: `./gradlew assemble`

To check development artifacts: `./gradlew check`

To clean all generated artifacts: `./gradlew clean`

## tools

These are the required tools.

- GNU Binutils version 2.34 target (see below)
- GNU GCC version 9.2 target (see below)
- GNU GDB version 7.1 target (see below)
- GNU GRUB version 2.04 target (see below)
- OpenJDK version 11 host

OpenJDK is required to run Gradle: we suggest AdoptOpenJDK builds.

Binutils, GCC and GDB are required for target `i686-pc-elf`.

GRUB is required for platforms `i386-qemu`, `i386-pc` and `i386-efi`.
For more information on GRUB, see [README.grub.md](README.grub.md).

There are useful scripts for building tools in [tools](tools).

## issues

- Gradle: [Assembler language support](https://github.com/gradle/gradle-native/issues/172)
- Gradle: [Built in support for mingw multi-architecture compilation](https://github.com/gradle/gradle-native/issues/969) 

# check

*TODO*: apply some technique for pure testing: running test programs in the host system with googletest. Requires multi tool support from Gradle.

*TODO*: apply some technique for emulator testing: running test programs in an emulator, somehow verifying post conditions. Requires emulator support.

*TODO*: apply some technique for integration testing: runnin test programs in actual metal, somehow verifying post conditions. Epic!

# use

## targets

These are the currently supported targets:

- `i686-pc-elf`

## gradle

Componets are Gradle projects meant for multi-project configurations.

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
