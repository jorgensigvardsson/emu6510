using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;

namespace Emu6510.Debugger.Application.Bridge
{
    public class Debugger : IDisposable
    {
        private readonly IntPtr m_debugger;
        private readonly unsafe byte* m_memoryView;

        public Debugger()
        {
            var error = DbgCreate(ref m_debugger);
            if (error != ErrorCode.Success)
                throw new ApplicationException($"DbgCreate error code: {error}");

            try
            {
                error = DbgGetMemoryPtr(m_debugger, out var ptr);
                if (error != ErrorCode.Success)
                    throw new ApplicationException($"DbgGetMemoryPtr error code: {error}");

                unsafe
                {
                    m_memoryView = (byte*) ptr.ToPointer();
                }
            }
            catch
            {
                DbgDestroy(m_debugger);
                m_debugger = IntPtr.Zero;
                throw;
            }
        }

        private void ReleaseUnmanagedResources()
        {
            DbgDestroy(m_debugger);
        }

        public void Dispose()
        {
            ReleaseUnmanagedResources();
            GC.SuppressFinalize(this);
        }

        ~Debugger()
        {
            ReleaseUnmanagedResources();
        }

        #region P/Invoke

        public const uint MemorySize = 64 * 1024;

        // ReSharper disable InconsistentNaming
        public enum ErrorCode
        {
            Success = 0,
            BadArgument = 1,
            BadInstruction = 2,
            NullArgument = 3,
            GeneralFailure = 666
        }
        // ReSharper restore InconsistentNaming

        [DllImport("Emu6510.Debugger.dll", EntryPoint = "dbg_create", SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I4)]
        static extern ErrorCode DbgCreate(ref IntPtr debugger);

        [DllImport("Emu6510.Debugger.dll", EntryPoint = "dbg_load_program", SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I4)]
        static extern ErrorCode DbgLoadProgram(IntPtr debugger, ushort memoryOffset, byte[] program, ushort programLength);

        [DllImport("Emu6510.Debugger.dll", EntryPoint = "dbg_get_memory_ptr", SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I4)]
        static extern ErrorCode DbgGetMemoryPtr(IntPtr debugger, out IntPtr ptr);

        [DllImport("Emu6510.Debugger.dll", EntryPoint = "dbg_step_one_instruction", SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I4)]
        static extern ErrorCode DbgStepOneInstruction(IntPtr debugger);
        
        [DllImport("Emu6510.Debugger.dll", EntryPoint = "dbg_destroy", SetLastError = false)]
        static extern void DbgDestroy(IntPtr debugger);
        #endregion
    }
}
