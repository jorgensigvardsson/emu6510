using System;
using System.IO;
using System.Windows;
using System.Windows.Input;
using Emu6510.Debugger.Application.Bridge;
using Emu6510.Debugger.Application.Ui.Infrastructure;
using Microsoft.Win32;

namespace Emu6510.Debugger.Application.Ui.MainWindow
{
    public class ViewModel : IViewModel
    {
        private readonly IDebugger m_debugger;
        private readonly IDialogService m_dialogService;
        private readonly RelayCommand m_openFile;

        public ViewModel(CodeView.IViewModel code, ProcessorView.IViewModel processor,
                         IDebugger debugger, IDialogService dialogService)
        {
            m_debugger = debugger ?? throw new ArgumentNullException(nameof(debugger));
            m_dialogService = dialogService ?? throw new ArgumentNullException(nameof(dialogService));
            Code = code ?? throw new ArgumentNullException(nameof(code));
            Processor = processor ?? throw new ArgumentNullException(nameof(processor));

            Code.Debugger = m_debugger;
            Processor.Debugger = m_debugger;
            m_openFile = new RelayCommand(OnOpenFile);
        }

        public CodeView.IViewModel Code { get; }
        public ProcessorView.IViewModel Processor { get; }
        public ICommand OpenFile => m_openFile;

        private void OnOpenFile()
        {
            var dialog = new OpenFileDialog
            {
                Multiselect = false,
                Filter = "6510 programs (*.prg)|*.prg|All files (*.*)|*.*"
            };

            if (dialog.ShowDialog() != true)
                return;
            
            var program = File.ReadAllBytes(dialog.FileName);

            var result = m_dialogService.Show<OffsetDialog.IViewModel>();

            try
            {
                m_debugger.LoadProgram(result.Offset, program);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
    }
}
