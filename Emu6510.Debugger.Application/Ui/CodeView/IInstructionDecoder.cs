﻿using System.Collections.ObjectModel;
using Emu6510.Debugger.Application.Bridge;

namespace Emu6510.Debugger.Application.Ui.CodeView
{
    public interface IInstructionDecoder
    {
        ObservableCollection<Instruction> DecodeInstructions(IDebugger debugger);
    }
}