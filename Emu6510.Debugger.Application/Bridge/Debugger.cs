using System;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace Emu6510.Debugger.Application.Bridge
{
    public class Debugger : IDisposable, IDebugger
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

        public void LoadProgram(ushort offset, byte[] program)
        {
            if (program.Length > ushort.MaxValue)
                throw new ArgumentOutOfRangeException(nameof(program), $"byte array too large, max length is {ushort.MaxValue}");

            DbgLoadProgram(m_debugger, offset, program, (ushort) program.Length);
        }

        public ReadOnlySpan<byte> MemoryView
        {
            get
            {
                unsafe
                {
                    return new Span<byte>(m_memoryView, (int) MemorySize);
                }
            }
        }

        public byte RegisterA
        {
            get
            {
                var error = DbgGetRegisters(m_debugger, out var a, out _, out _, out _, out _, out _);
                if (error != ErrorCode.Success)
                    throw new ApplicationException($"DbgGetRegisters error code: {error}");
                return a;
            }
        }

        public byte RegisterX
        {
            get
            {
                var error = DbgGetRegisters(m_debugger, out _, out var x, out _, out _, out _, out _);
                if (error != ErrorCode.Success)
                    throw new ApplicationException($"DbgGetRegisters error code: {error}");
                return x;
            }
        }

        public byte RegisterY
        {
            get
            {
                var error = DbgGetRegisters(m_debugger, out _, out _, out var y, out _, out _, out _);
                if (error != ErrorCode.Success)
                    throw new ApplicationException($"DbgGetRegisters error code: {error}");
                return y;
            }
        }

        public ushort RegisterPc
        {
            get
            {
                var error = DbgGetRegisters(m_debugger, out _, out _, out _, out var pc, out _, out _);
                if (error != ErrorCode.Success)
                    throw new ApplicationException($"DbgGetRegisters error code: {error}");
                return pc;
            }
        }

        public byte RegisterS
        {
            get
            {
                var error = DbgGetRegisters(m_debugger, out _, out _, out _, out _, out var s, out _);
                if (error != ErrorCode.Success)
                    throw new ApplicationException($"DbgGetRegisters error code: {error}");
                return s;
            }
        }

        public byte RegisterP
        {
            get
            {
                var error = DbgGetRegisters(m_debugger, out _, out _, out _, out _, out _, out var p);
                if (error != ErrorCode.Success)
                    throw new ApplicationException($"DbgGetRegisters error code: {error}");
                return p;
            }
        }

        public Instruction Decode(ushort address)
        {
            var pc = address;
            var error = DbgDecode(m_debugger, ref pc, out var decodedInstruction);
            if (error != ErrorCode.Success)
                throw new ApplicationException($"DbgDecode error code: {error}");

            return new Instruction
            {
                Mnemonics = Encoding.UTF8.GetString(decodedInstruction.DecodedOp.TakeWhile(c => c != 0).ToArray()),
                Address = address,
                Bytes = MemoryView.Slice(address, (int) decodedInstruction.OpLen)
            };
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
        public const int MaxDecodedOpLen = 16;

        [StructLayout(LayoutKind.Sequential, Pack = 4)]
        public struct DecodedInstruction
        {
            [MarshalAs(UnmanagedType.U1)]
            public bool IsValidOp;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = MaxDecodedOpLen)]
            public byte[] DecodedOp;
            [MarshalAs(UnmanagedType.U2)]
            public ushort OpStartAddr;
            [MarshalAs(UnmanagedType.U4)]
            public uint OpLen;
        }

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

        [DllImport("Emu6510.Debugger.dll", EntryPoint = "dbg_get_registers", SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I4)]
        static extern ErrorCode DbgGetRegisters(IntPtr debugger, out byte a, out byte x, out byte y, out ushort pc, out byte s, out byte p);

        [DllImport("Emu6510.Debugger.dll", EntryPoint = "dbg_decode", SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I4)]
        static extern ErrorCode DbgDecode(IntPtr debugger, ref ushort pc, out DecodedInstruction decodedInstruction);

        [DllImport("Emu6510.Debugger.dll", EntryPoint = "dbg_destroy", SetLastError = false)]
        static extern void DbgDestroy(IntPtr debugger);
        #endregion
    }
}
