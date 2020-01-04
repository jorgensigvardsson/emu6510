using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;

namespace Emu6510.Debugger.Application.Ui.CodeView
{
    public interface IInstructionDecoder
    {
        ObservableCollection<Instruction> DecodeInstructions(ReadOnlySpan<byte> memoryView);
    }
}