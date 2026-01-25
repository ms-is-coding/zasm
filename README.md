# zasm

zasm is a small, experimental assembler.

It takes a single assembly source file and produces an **ELF executable**. Nothing fancy, nothing hidden. The goal is to stay understandable, hackable, and honest about what it does.

This project is intentionally minimal. Think of it as a playground for learning how assemblers and object formats work, without the weight of a full toolchain.

---

## Features

* Simple custom assembly syntax
* Direct machine code generation
* ELF output
* Minimal abstractions
* Easy to read codebase

---

## Usage

```
zasm input.zasm -o output
```

This reads `input.zasm` and emits an ELF executable named `output`.

---

## Status

zasm is a work in progress.

Things may change. Instructions may move. Formats may break. That is part of the fun.

---

## Non-goals

* Full compatibility with existing assemblers
* Complex macro systems
* Optimizations
* Being production-ready

If you want something battle-tested, use an established assembler. If you want to see how the gears turn, you are in the right place.

---

## License

MIT

