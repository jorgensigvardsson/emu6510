using System;

namespace Emu6510.Debugger.Application.Ui.Infrastructure
{
    public interface IDialogService
    {
        TViewModel Show<TViewModel>() where TViewModel : IDialogViewModel;
        TViewModel Show<TViewModel>(Action<TViewModel> init) where TViewModel : IDialogViewModel;
    }
}