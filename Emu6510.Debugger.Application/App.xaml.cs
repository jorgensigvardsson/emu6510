using System;
using System.ComponentModel;
using System.Diagnostics;
using System.Windows;
using Autofac;
using IContainer = Autofac.IContainer;

namespace Emu6510.Debugger.Application
{
    public partial class App
    {
        private static bool? s_isInDesignMode;

        protected override void OnStartup(StartupEventArgs e)
        {
            if (!IsInDesignModeStatic)
            {
                IContainer container = null!;
                var builder = new ContainerBuilder();
                builder.RegisterModule<AutofacModule>();
                builder.RegisterInstance(new ResolverProxy(new Lazy<IContainer>(() => container)))
                       .As<IResolverProxy>();
                container = builder.Build();

                var mainWindow = container.Resolve<Ui.MainWindow.View>();
                mainWindow.DataContext = container.Resolve<Ui.MainWindow.IViewModel>();
                mainWindow.Show();

                ShutdownMode = ShutdownMode.OnMainWindowClose;
            }

            base.OnStartup(e);
        }

        public static bool IsInDesignModeStatic
        {
            // Stolen from MVVM Light
            get
            {
                if (!s_isInDesignMode.HasValue)
                {
                    var prop = DesignerProperties.IsInDesignModeProperty;
                    s_isInDesignMode
                        = (bool)DependencyPropertyDescriptor
                                .FromProperty(prop, typeof(FrameworkElement))
                                .Metadata.DefaultValue;

                    // Just to be sure
                    if (!s_isInDesignMode.Value && Process.GetCurrentProcess().ProcessName.StartsWith("devenv", StringComparison.Ordinal))
                        s_isInDesignMode = true;
                }

                return s_isInDesignMode.Value;
            }
        }
    }
}
