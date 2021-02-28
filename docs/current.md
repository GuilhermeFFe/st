# Staple VM Specs

## Symbols

'#' means number constant

## Instructions

* `PUSH`        - Push an 8bit number onto the stack
* `ADD`         - Pops last two number off of stack, adds, pushes result
* `HTL`         - Pops stack and returns result as exit code

## Example

```
push #30
push #12
add
hlt
```

* push        => Instruction, PUSH, 1
* #30         => Number, 30, 1
* push        => Instruction, PUSH, 2
* #12         => Number, 12, 2
* add         => Instruction, ADD, 3
* hlt         => Instruction, HLT, 4