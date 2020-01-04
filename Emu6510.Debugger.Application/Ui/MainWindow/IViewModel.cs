using System.Windows.Input;

namespace Emu6510.Debugger.Application.Ui.MainWindow
{
    public interface IViewModel
    {
        CodeView.IViewModel Code { get; }
        ProcessorView.IViewModel Processor { get; }
        ICommand OpenFile { get; }
    }
}