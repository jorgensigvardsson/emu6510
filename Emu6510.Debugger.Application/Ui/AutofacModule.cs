﻿using Autofac;

namespace Emu6510.Debugger.Application.Ui
{
    public class AutofacModule : Module
    {
        protected override void Load(ContainerBuilder builder)
        {
            builder.RegisterType<MainWindow.View>();
            builder.RegisterType<MainWindow.ViewModel>()
                   .As<MainWindow.IViewModel>();
            
            builder.RegisterType<CodeView.ViewModel>()
                   .As<CodeView.IViewModel>();
            builder.RegisterType<CodeView.InstructionDecoder>()
                   .As<CodeView.IInstructionDecoder>();

            builder.RegisterType<ProcessorView.ViewModel>()
                   .As<ProcessorView.IViewModel>();

            builder.RegisterType<OffsetDialog.ViewModel>()
                   .As<OffsetDialog.IViewModel>();
            builder.RegisterType<OffsetDialog.View>();

            builder.RegisterType<Infrastructure.DialogService>()
                   .As<Infrastructure.IDialogService>()
                   .SingleInstance();
        }
    }
}
