using System.Collections.ObjectModel;
using Emu6510.Debugger.Application.Bridge;

namespace Emu6510.Debugger.Application.Ui.CodeView
{
    public interface IViewModel
    {
        IDebugger? Debugger { set; get; }
        ObservableCollection<Instruction> Instructions { get; }
        void Refresh();
    }
}