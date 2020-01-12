using System;
using System.Collections.Generic;
using System.Text;

namespace Emu6510.Debugger.Application.Ui.Infrastructure
{
    public interface IDialogViewModel
    {
        bool Cancelled { set; get; }
    }
}
