using Autofac;

namespace Emu6510.Debugger.Application
{
    public class AutofacModule : Module
    {
        protected override void Load(ContainerBuilder builder)
        {
            builder.RegisterModule<Ui.AutofacModule>();
        }
    }
}