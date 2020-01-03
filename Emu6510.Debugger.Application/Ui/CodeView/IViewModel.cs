using System.Collections.ObjectModel;

namespace Emu6510.Debugger.Application.Ui.CodeView
{
    public interface IViewModel
    {
        ObservableCollection<Instruction> Instructions { get; }
    }
}