using System;
using Autofac;

namespace Emu6510.Debugger.Application
{
    public class ResolverProxy : IResolverProxy
    {
        private readonly Lazy<IContainer> m_container;

        public ResolverProxy(Lazy<IContainer> container)
        {
            m_container = container;
        }

        public T Resolve<T>()
        {
            return m_container.Value.Resolve<T>();
        }

        public object Resolve(Type t)
        {
            return m_container.Value.Resolve(t);
        }
    }
}