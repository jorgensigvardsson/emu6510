using Emu6510.Debugger.Application.Bridge;

namespace Emu6510.Debugger.Application.Ui.ProcessorView
{
    public class DesignViewModel : IViewModel
    {
        public IDebugger? Debugger { get; set; }
        public byte RegisterA { get; } = 0x03;
        public byte RegisterX { get; } = 0x23;
        public byte RegisterY { get; } = 0xF8;
        public ushort RegisterPc { get; } = 0x231A;
        public byte RegisterS { get; } = 0xF3;
        public byte RegisterP { get; } = 0b0000001;
    }
}