using System;
using Emu6510.Debugger.Application.Bridge;

namespace Emu6510.Debugger.Application.Ui.ProcessorView
{
    public class ViewModel : ViewModelBase, IViewModel
    {
        private IDebugger? m_debugger;
        private byte m_registerA;
        private byte m_registerX;
        private byte m_registerY;
        private ushort m_registerPc;
        private byte m_registerS;
        private byte m_registerP;

        public IDebugger? Debugger
        {
            get => m_debugger;
            set
            {
                m_debugger = value;
                UpdateRegisters();
                OnPropertyChanged();
            }
        }

        private void UpdateRegisters()
        {
            RegisterA = m_debugger?.RegisterA ?? 0;
            RegisterX = m_debugger?.RegisterX ?? 0;
            RegisterY = m_debugger?.RegisterY ?? 0;
            RegisterPc = m_debugger?.RegisterPc ?? 0;
            RegisterS = m_debugger?.RegisterS ?? 0;
            RegisterP = m_debugger?.RegisterP ?? 0;
        }

        public byte RegisterA
        {
            get => m_registerA;
            private set
            {
                m_registerA = value;
                OnPropertyChanged();
            }
        }

        public byte RegisterX
        {
            get => m_registerX;
            private set
            {
                m_registerX = value;
                OnPropertyChanged();
            }
        }

        public byte RegisterY
        {
            get => m_registerY;
            private set
            {
                m_registerY = value;
                OnPropertyChanged();
            }
        }

        public ushort RegisterPc
        {
            get => m_registerPc;
            private set
            {
                m_registerPc = value;
                OnPropertyChanged();
            }
        }

        public byte RegisterS
        {
            get => m_registerS;
            private set
            {
                m_registerS = value;
                OnPropertyChanged();
            }
        }

        public byte RegisterP
        {
            get => m_registerP;
            private set
            {
                m_registerP = value;
                OnPropertyChanged();
            }
        }
    }
}
