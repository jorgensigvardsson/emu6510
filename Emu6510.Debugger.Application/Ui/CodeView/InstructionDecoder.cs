using System;
using System.Collections.ObjectModel;
using System.Linq;
using Emu6510.Debugger.Application.Bridge;

namespace Emu6510.Debugger.Application.Ui.CodeView
{
    public class InstructionDecoder : IInstructionDecoder
    {
        public ObservableCollection<Instruction> DecodeInstructions(IDebugger debugger)
        {
            var result = new ObservableCollection<Instruction>();
            var memory = debugger.MemoryView;
            for (var i = 0; i < memory.Length;)
            {
                result.Add(DecodeInstruction(debugger, ref i));
            }

            return result;
        }

        private Instruction DecodeInstruction(IDebugger debugger, ref int ptr)
        {
            var instr = debugger.Decode((ushort) ptr);
            ptr += instr.Bytes.Length;
            return new Instruction(
                address: instr.Address,
                hexRepresentation: string.Join("", instr.Bytes.ToArray().Select(b => b.ToString("X2"))),
                jumpLabel: null,
                mnemonics: instr.Mnemonics
            );
        }
    }
}
