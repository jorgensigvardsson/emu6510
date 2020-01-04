using System;

namespace Emu6510.Debugger.Application.Bridge
{
    public interface IDebugger
    {
        ReadOnlySpan<byte> MemoryView { get; }
        byte RegisterA { get; }
        byte RegisterX { get; }
        byte RegisterY { get; }
        ushort RegisterPc { get; }
        byte RegisterS { get; }
        byte RegisterP { get; }
    }
}