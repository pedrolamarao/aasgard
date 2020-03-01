Date: 2020-01-03

# summary

`gradle-gdb` teaches Gradle how to drive GDB processes.

Use it together with `cpp-application`.

# use

To create new tasks, use the `gdb` extension:

```groovy
binaries.whenElementFinalized { binary ->
    def gdbTask = gdb.register('GdbTask') {
        target = binary.executableFile
    }
}

```

# configure

Properties:

- `executable` — GDB executable
- `listeners` — list of `GdbMiListener`
- `script` — closure on `GdbMiProcess`
- `target` — program image

## references

_TODO_
