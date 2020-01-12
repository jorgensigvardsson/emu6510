using Emu6510.Debugger.Application.Ui.Infrastructure;

namespace Emu6510.Debugger.Application.Ui.OffsetDialog
{
    public interface IViewModel : IDialogViewModel
    {
        ushort Offset { set; get; }
    }
}
