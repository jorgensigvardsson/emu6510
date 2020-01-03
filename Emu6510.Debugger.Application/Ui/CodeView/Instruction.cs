using System;
using System.Collections.Generic;
using System.Text;

namespace Emu6510.Debugger.Application.Ui.CodeView
{
    public class Instruction
    {
        public Instruction(ushort address, string hexRepresentation, string? jumpLabel, string mnemonics)
        {
            Address = address;
            HexRepresentation = hexRepresentation ?? throw new ArgumentNullException(nameof(hexRepresentation));
            JumpLabel = jumpLabel;
            Mnemonics = mnemonics ?? throw new ArgumentNullException(nameof(mnemonics));
        }

        public UInt16 Address { get; }
        public string HexRepresentation { get; }
        public string? JumpLabel { get; } // TODO: implement me
        public string Mnemonics { get; }
    }
}
