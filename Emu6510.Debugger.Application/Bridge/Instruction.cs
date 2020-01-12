using System;

namespace Emu6510.Debugger.Application.Bridge
{
    public ref struct Instruction
    {
        public string Mnemonics;
        public ushort Address;
        public ReadOnlySpan<byte> Bytes;
    }
}