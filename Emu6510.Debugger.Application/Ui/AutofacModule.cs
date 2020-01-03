using System.ComponentModel;
using Autofac;

namespace Emu6510.Debugger.Application.Ui
{
    public class AutofacModule : Module
    {
        protected override void Load(ContainerBuilder builder)
        {
            if (RootDataContext.IsInDesignModeStatic)
            {
                builder.RegisterType<MainWindow.DesignViewModel>()
                       .As<MainWindow.IViewModel>();
            }
            else
            {
                builder.RegisterType<MainWindow.ViewModel>()
                       .As<MainWindow.IViewModel>();
            }
        }
    }
}
