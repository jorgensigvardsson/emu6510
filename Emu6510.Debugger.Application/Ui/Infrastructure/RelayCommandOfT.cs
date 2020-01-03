using System;
using System.Windows.Input;

namespace Emu6510.Debugger.Application.Ui.Infrastructure
{
    public class RelayCommand<T> : ICommand
    {
        private readonly Action<T> m_execute;

        private readonly Predicate<T>? m_canExecute;

        public RelayCommand(Action<T> execute)
            : this(execute, null)
        {
        }

        public RelayCommand(Action<T> execute, Predicate<T>? canExecute)
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
            return m_canExecute?.Invoke((T)parameter) ?? true;
        }

        public void Execute(object parameter)
        {
            m_execute((T)parameter);
        }
    }
}