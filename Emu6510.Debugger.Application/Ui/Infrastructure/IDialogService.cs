using System;

namespace Emu6510.Debugger.Application.Ui.Infrastructure
{
    public interface IDialogService
    {
        TViewModel Show<TViewModel>();
        TViewModel Show<TViewModel>(Action<TViewModel> init);
    }
}