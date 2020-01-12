using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;

namespace Emu6510.Debugger.Application.Ui.CodeView
{
    public class InstructionDecoder : IInstructionDecoder
    {
        public ObservableCollection<Instruction> DecodeInstructions(ReadOnlySpan<byte> memoryView)
        {
            var result = new ObservableCollection<Instruction>();
            for (var i = 0; i < memoryView.Length;)
            {
                result.Add(DecodeInstruction(memoryView, ref i));
            }

            return result;
        }

        private Instruction DecodeInstruction(in ReadOnlySpan<byte> memoryView, ref int ptr)
        {
            // TODO: Implement me properly!
            const int MaxUnknownRange = 16;
            ushort address = (ushort) ptr;

            var bytes = new byte[MaxUnknownRange];
            var i = 0;
            for (; i + ptr < memoryView.Length && i < MaxUnknownRange; ++i)
            {
                bytes[i] = memoryView[i + ptr];
                ++ptr;
            }

            return new Instruction(
                address: address,
                hexRepresentation: string.Join("", bytes.Take(i).Select(b => b.ToString("X2"))),
                jumpLabel: null,
                mnemonics: "DB " + string.Join(", ", bytes.Take(i).Select(b => b.ToString("X2")))
            );
        }
    }
}
