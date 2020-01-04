using System.Windows;

namespace Emu6510.Debugger.Application.Ui.MainWindow
{
    public partial class View
    {
        public View()
        {
            InitializeComponent();
        }

        private void OnExit(object sender, RoutedEventArgs e)
        {
            System.Windows.Application.Current.Shutdown();
        }
    }
}
