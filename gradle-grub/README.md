Date: 2020-03-01

# summary

`gradle-grub` teaches Gradle how to compile GRUB images.

Use it together with `cpp-application`.

# use

To create new tasks, use the `grub` extension:

```gradle
binaries.whenElementFinalized { binary -> 
    def grubRescue = grub.rescue("grubRescue") {
        executable binary
    }
    def grubStandalone = grub.standalone("grubRescue") {
        format 'i386-qemu'
        executable binary
    }
```

# configure

## `rescue`

Properties:

- `fonts` — fonts to install [default: empty]
- `install` — modules to install [default: all]
- `load` — modules to pre-load [default: none]
- `locales` — locales to install [default: empty]
- `source` — program file to start [required]
- `target` — image file to create [required]
- `themes` — themes to install [default: empty]

Utilities:

- `executable` — defines default `source` and `target` for `CppExecutable`

## `standalone`

Properties:

- `fonts` — fonts to install [default: none]
- `format` — image format [required]
- `install` — modules to install [default: all]
- `load` — modules to pre-load [default: none]
- `locales` — locales to install [default: none]
- `source` — program file to start [required]
- `target` — image file to create [required]
- `themes` — themes to install [default: none]

Utilities:

- `executable` — defines default `source` and `target` for `CppExecutable`

## references

_TODO_
