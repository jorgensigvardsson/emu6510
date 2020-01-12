using System;
using System.Collections.Generic;
using System.Windows;

namespace Emu6510.Debugger.Application.Ui.Infrastructure
{
    public class DialogService : IDialogService
    {
        private readonly IResolverProxy m_resolverProxy;
        private readonly IDictionary<Type, Type> m_dialogViews = new Dictionary<Type, Type>();

        public DialogService(IResolverProxy resolverProxy)
        {
            m_resolverProxy = resolverProxy ?? throw new ArgumentNullException(nameof(resolverProxy));
            m_dialogViews[typeof(OffsetDialog.IViewModel)] = typeof(OffsetDialog.View);
        }

        public TViewModel Show<TViewModel>(Action<TViewModel> init) where TViewModel : IDialogViewModel
        {
            var viewModel = m_resolverProxy.Resolve<TViewModel>();
            init(viewModel);
            var dialog = (Window) m_resolverProxy.Resolve(m_dialogViews[typeof(TViewModel)]);
            dialog.DataContext = viewModel;
            dialog.ShowDialog();
            return viewModel;
        }

        public TViewModel Show<TViewModel>() where TViewModel : IDialogViewModel
        {
            var viewModel = m_resolverProxy.Resolve<TViewModel>();
            var dialog = (Window)m_resolverProxy.Resolve(m_dialogViews[typeof(TViewModel)]);
            dialog.DataContext = viewModel;
            dialog.ShowDialog();
            return viewModel;
        }
    }
}
