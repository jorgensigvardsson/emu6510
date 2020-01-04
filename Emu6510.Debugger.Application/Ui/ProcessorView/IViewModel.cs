using System.Collections.ObjectModel;
using Emu6510.Debugger.Application.Bridge;

namespace Emu6510.Debugger.Application.Ui.ProcessorView
{
    public interface IViewModel
    {
        IDebugger? Debugger { set; get; }

        byte RegisterA { get; }
        byte RegisterX { get; }
        byte RegisterY { get; }
        ushort RegisterPc { get; }
        byte RegisterS { get; }
        byte RegisterP { get; }
    }
}