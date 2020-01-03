using System;

namespace Emu6510.Debugger.Application.Ui.MainWindow
{
    public class ViewModel : IViewModel
    {
        public ViewModel(CodeView.IViewModel code, ProcessorView.IViewModel processor)
        {
            Code = code ?? throw new ArgumentNullException(nameof(code));
            Processor = processor ?? throw new ArgumentNullException(nameof(processor));
        }

        public CodeView.IViewModel Code { get; }
        public ProcessorView.IViewModel Processor { get; }
    }
}
