using Autofac;

namespace Emu6510.Debugger.Application.Bridge
{
    public class AutofacModule : Module
    {
        protected override void Load(ContainerBuilder builder)
        {
            builder.RegisterType<Debugger>()
                   .As<IDebugger>();
        }
    }
}
