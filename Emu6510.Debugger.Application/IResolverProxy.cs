using System;

namespace Emu6510.Debugger.Application
{
    public interface IResolverProxy
    {
        T Resolve<T>();
        object Resolve(Type t);
    }
}