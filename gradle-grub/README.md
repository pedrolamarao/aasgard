Date: 2020-02-15

# summary

`gradle-grub` teaches Gradle how to compile GRUB images.

Use it together with `cpp-application`.

# use

Create new tasks with type `GrubStandaloneCompile` or `GrubRescueCompile`.

Let `binary` be a `CppExecutable`:

```gradle
tasks.register("grubRescue_${binary.name}", aasgard.gradle.grub.GrubRescueCompile) {
    executable binary
}
```

`GrubRescueCompile` shall create a GRUB image with the binary and appropriate configuration.

## `aasgard.gradle.grub.GrubRescueCompile`

Properties:

- `executable` — `CppExecutable` to install
- `install` — modules to install
- `load` — modules to pre-load

## references

_TODO_
