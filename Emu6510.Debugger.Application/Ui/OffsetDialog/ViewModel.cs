namespace Emu6510.Debugger.Application.Ui.OffsetDialog
{
    public class ViewModel : IViewModel
    {
        public ushort Offset { get; set; }
        public bool Cancelled { get; set; }
    }
}