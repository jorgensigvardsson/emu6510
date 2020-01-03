using System;
using System.ComponentModel;
using System.Diagnostics;
using System.Windows;
using Autofac;
using IContainer = Autofac.IContainer;

namespace Emu6510.Debugger.Application
{
    public class RootDataContext
    {
        private static bool? m_isInDesignMode;

        public RootDataContext()
        {
            var container = CreateContainer();
            MainWindowViewModel = container.Resolve<Ui.MainWindow.IViewModel>();
        }

        private IContainer CreateContainer()
        {
            var containerBuilder = new ContainerBuilder();
            containerBuilder.RegisterModule<Ui.AutofacModule>();
            return containerBuilder.Build();
        }

        public Ui.MainWindow.IViewModel MainWindowViewModel { get; }

        public static bool IsInDesignModeStatic
        {
            get
            {
                if (!m_isInDesignMode.HasValue)
                {
                    var prop = DesignerProperties.IsInDesignModeProperty;
                    m_isInDesignMode
                        = (bool)DependencyPropertyDescriptor
                                .FromProperty(prop, typeof(FrameworkElement))
                                .Metadata.DefaultValue;

                    // Just to be sure
                    if (!m_isInDesignMode.Value
                        && Process.GetCurrentProcess().ProcessName.StartsWith("devenv", StringComparison.Ordinal))
                    {
                        m_isInDesignMode = true;
                    }
                }

                return m_isInDesignMode.Value;
            }
        }
    }
}
