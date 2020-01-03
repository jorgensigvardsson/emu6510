using System;
using System.Windows.Input;

namespace Emu6510.Debugger.Application.Ui.Infrastructure
{
    public class RelayCommand : ICommand
    {
        private readonly Action m_execute;
        private readonly Func<bool>? m_canExecute;

        public RelayCommand(Action execute)
            : this(execute, null)
        {
        }

        public RelayCommand(Action execute, Func<bool>? canExecute)
        {
            m_execute = execute ?? throw new ArgumentNullException(nameof(execute));
            m_canExecute = canExecute;
        }

        public event EventHandler CanExecuteChanged
        {
            add
            {
                if (m_canExecute != null)
                {
                    CommandManager.RequerySuggested += value;
                }
            }

            remove
            {
                if (m_canExecute != null)
                {
                    CommandManager.RequerySuggested -= value;
                }
            }
        }

        public void RaiseCanExecuteChanged()
        {
            CommandManager.InvalidateRequerySuggested();
        }

        public bool CanExecute(object parameter)
        {
            return m_canExecute == null || m_canExecute();
        }

        public void Execute(object parameter)
        {
            m_execute();
        }
    }
}
