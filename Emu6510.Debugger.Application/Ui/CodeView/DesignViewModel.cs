using System.Collections.ObjectModel;
using Emu6510.Debugger.Application.Bridge;

namespace Emu6510.Debugger.Application.Ui.CodeView
{
    public class DesignViewModel : IViewModel
    {
        public IDebugger? Debugger { get; set; }

        public ObservableCollection<Instruction> Instructions { get; } = new ObservableCollection<Instruction>(
            new []
            {
                new Instruction(address: 0x0000, hexRepresentation: "EA", jumpLabel: null, mnemonics: "NOP"),
                new Instruction(address: 0x0001, hexRepresentation: "A23212", jumpLabel: null, mnemonics: "LDA $(32, X)"),

                new Instruction(address: 0x0001, hexRepresentation: "A23212", jumpLabel: null, mnemonics: "LDA $(32, X)"),

                new Instruction(address: 0x0001, hexRepresentation: "A23212", jumpLabel: null, mnemonics: "LDA $(32, X)"),

                new Instruction(address: 0x0001, hexRepresentation: "A23212", jumpLabel: null, mnemonics: "LDA $(32, X)"),

                new Instruction(address: 0x0001, hexRepresentation: "A23212", jumpLabel: null, mnemonics: "LDA $(32, X)"),

                new Instruction(address: 0x0001, hexRepresentation: "A23212", jumpLabel: null, mnemonics: "LDA $(32, X)"),

                new Instruction(address: 0x0001, hexRepresentation: "A23212", jumpLabel: null, mnemonics: "LDA $(32, X)"),

                new Instruction(address: 0x0001, hexRepresentation: "A23212", jumpLabel: null, mnemonics: "LDA $(32, X)"),

                new Instruction(address: 0x0001, hexRepresentation: "A23212", jumpLabel: null, mnemonics: "LDA $(32, X)"),

                new Instruction(address: 0x0001, hexRepresentation: "A23212", jumpLabel: null, mnemonics: "LDA $(32, X)"),

                new Instruction(address: 0x0001, hexRepresentation: "A23212", jumpLabel: null, mnemonics: "LDA $(32, X)"),

                new Instruction(address: 0x0001, hexRepresentation: "A23212", jumpLabel: null, mnemonics: "LDA $(32, X)"),

                new Instruction(address: 0x0001, hexRepresentation: "A23212", jumpLabel: null, mnemonics: "LDA $(32, X)"),

                new Instruction(address: 0x0001, hexRepresentation: "A23212", jumpLabel: null, mnemonics: "LDA $(32, X)"),

                new Instruction(address: 0x0001, hexRepresentation: "A23212", jumpLabel: null, mnemonics: "LDA $(32, X)"),

                new Instruction(address: 0x0001, hexRepresentation: "A23212", jumpLabel: null, mnemonics: "LDA $(32, X)"),

                new Instruction(address: 0x0001, hexRepresentation: "A23212", jumpLabel: null, mnemonics: "LDA $(32, X)"),

                new Instruction(address: 0x0001, hexRepresentation: "A23212", jumpLabel: null, mnemonics: "LDA $(32, X)"),

                new Instruction(address: 0x0001, hexRepresentation: "A23212", jumpLabel: null, mnemonics: "LDA $(32, X)"),

                new Instruction(address: 0x0001, hexRepresentation: "A23212", jumpLabel: null, mnemonics: "LDA $(32, X)"),

            }
        );

        public void Refresh()
        {
            throw new System.NotImplementedException();
        }
    }
}