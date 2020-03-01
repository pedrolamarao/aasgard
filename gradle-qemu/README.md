Date: 2020-03-01

# summary

`gradle-qemu` teaches Gradle how to run QEMU processes.

Use it together with `cpp-application`.

# use

To create new tasks, use the `qemu` extension:

```gradle
binaries.whenElementFinalized { binary -> 
    def qemuSystem = qemu.system("qemuSystem") {
        architecture = 'i386'
        bios = binary.get().executableFile
    }
}
```

# configure

## `system`

Properties:

- `architecture` — QEMU target architecture (e.g. `i386`) [required]
- `bios` — BIOS program
- `cdrom` — CD-ROM image
- `display` — type of display (e.g. `none`)
- `gdb` — GDB server (e.g. `tcp::1234`)
- `kernel` — Linux compatible program
- `start` — true to start, false to pause [default: true]

## references

- [QEMU](https://wiki.qemu.org/)
