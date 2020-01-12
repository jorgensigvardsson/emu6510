using System.Windows;
using Emu6510.Debugger.Application.Ui.Infrastructure;

namespace Emu6510.Debugger.Application.Ui.OffsetDialog
{
    public partial class View
    {
        public View()
        {
            InitializeComponent();
        }

        private void OnOk(object sender, RoutedEventArgs e)
        {
            ((IDialogViewModel)DataContext).Cancelled = false;
            Close();
        }

        private void OnCancel(object sender, RoutedEventArgs e)
        {
            ((IDialogViewModel)DataContext).Cancelled = true;
            Close();
        }
    }
}
