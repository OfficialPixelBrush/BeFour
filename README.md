# BeFour
The BeFour/B4/Be4 is a simplistic 4-Bit, TTL Processor, largely inspired by the Zilog Z80 and similar architectures of the late-1970s and early-1980s, just in 4-Bit.

# Goal
It's main idea is simple. How basic can I make an instruction set, while still making it somewhat useful?
This question arose out of need. I was originally trying to make a Diode-Transistor Logic Computer entirely from Scratch, which was meant to be 4-Bit too. However, planning that monstrocity became too difficult for my current skill-set, so I decided to try anew. My main goal not being an impressive instruction set, but something simple that won't require heaps of individual Diodes and Transistors. This is also why I'll be sticking with bog-standard TTL Chips for this project.

# Architecture
This Processor is entirely 4-Bit, aside from the Address Bus, which is 8-Bit.
This allows for Addressing of up to 256 Bytes of Memory, at least as a Program. The Processor is only capable of reading a 4-Bit address for RAM access, limiting it's Memory on that front to only 16 Bytes.

For more information about the Architecture, Instruction Set, Memory Map, et cetera, please [visit the Wiki page](https://github.com/OfficialPixelBrush/BeFour/wiki).

# Emulator
The provide Emulator is accurate enough for most simple Programs, and can be compiled easily with gcc.
Pre-built Binaries can usually be found in the Releases section, although these may not always be up-to-date.

## How to use
The emulator takes two parameters. The first is the filename of whichever Binary file it's supposed to execute. The second is how many instructions it'll execute before stopping. By default, this is -1, meaning it'll stop right away.

### Windows
To execute the provided Fibonacci Program, for example, one could use `.\b4emu.exe ..\software\fibo.bin 50` to execute the Fibbonaci Program for 50 Instructions.

### Linux
Similar to Windows, just different formatting:
`./b4emu ../software/fibo.bin 50`
Outside of that, make sure the binary is set to be executable.
`chmod +x b4emu`

## Binaries
You can find all Releases in the [Releases Section](https://github.com/OfficialPixelBrush/BeFour/releases).

# License
It's been difficult finding a proper license for this thus far, especially because I don't see why anyone'd want to do much with this thing.
It's my processor, feel free to be inspired by it, but don't steal it, and don't use it commercially. I'll probably replace this with a proper license sometime soon, but if you have any deeper questions, just shoot me a message via an Issue or something.
