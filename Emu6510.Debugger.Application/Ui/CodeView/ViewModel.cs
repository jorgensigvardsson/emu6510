using System.Collections.ObjectModel;

namespace Emu6510.Debugger.Application.Ui.CodeView
{
    public class ViewModel : IViewModel
    {
        public ObservableCollection<Instruction> Instructions { get; } = new ObservableCollection<Instruction>();
    }
}
