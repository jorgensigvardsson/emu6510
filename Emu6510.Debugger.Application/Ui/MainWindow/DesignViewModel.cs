namespace Emu6510.Debugger.Application.Ui.MainWindow
{
    public class DesignViewModel : IViewModel
    {
        public CodeView.IViewModel Code { get; } = new CodeView.DesignViewModel();
        public ProcessorView.IViewModel Processor { get; } = new ProcessorView.DesignViewModel();
    }
}