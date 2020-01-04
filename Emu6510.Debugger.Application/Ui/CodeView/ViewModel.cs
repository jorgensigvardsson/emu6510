using System;
using System.Collections.ObjectModel;
using Emu6510.Debugger.Application.Bridge;

namespace Emu6510.Debugger.Application.Ui.CodeView
{
    public class ViewModel : ViewModelBase, IViewModel
    {
        private readonly IInstructionDecoder m_instructionDecoder;
        private IDebugger? m_debugger;
        private ObservableCollection<Instruction> m_instructions = new ObservableCollection<Instruction>();

        public ViewModel(IInstructionDecoder instructionDecoder)
        {
            m_instructionDecoder = instructionDecoder ?? throw new ArgumentNullException(nameof(instructionDecoder));
        }

        public IDebugger? Debugger
        {
            get => m_debugger;
            set
            {
                m_debugger = value;
                GenerateInstructions();
                OnPropertyChanged();
            }
        }

        public ObservableCollection<Instruction> Instructions
        {
            get => m_instructions;
            set
            {
                m_instructions = value; 
                OnPropertyChanged();
            }
        }

        private void GenerateInstructions()
        {
            Instructions.Clear();
            if (m_debugger == null)
                return;

            m_instructions = m_instructionDecoder.DecodeInstructions(m_debugger.MemoryView);
        }
    }
}
