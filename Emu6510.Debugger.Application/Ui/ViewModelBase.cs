using System.ComponentModel;
using System.Runtime.CompilerServices;
using Emu6510.Debugger.Application.Annotations;

namespace Emu6510.Debugger.Application.Ui
{
    public abstract class ViewModelBase : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler? PropertyChanged;

        [NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string? propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
