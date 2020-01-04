using System;
using Emu6510.Debugger.Application.Bridge;

namespace Emu6510.Debugger.Application.Ui.MainWindow
{
    public class ViewModel : IViewModel
    {
        private readonly IDebugger m_debugger;

        public ViewModel(CodeView.IViewModel code, ProcessorView.IViewModel processor,
                         IDebugger debugger)
        {
            m_debugger = debugger ?? throw new ArgumentNullException(nameof(debugger));
            Code = code ?? throw new ArgumentNullException(nameof(code));
            Processor = processor ?? throw new ArgumentNullException(nameof(processor));

            Code.Debugger = m_debugger;
            Processor.Debugger = m_debugger;
        }

        public CodeView.IViewModel Code { get; }
        public ProcessorView.IViewModel Processor { get; }
    }
}
