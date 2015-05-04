TEMPLATE = lib
TARGET = cot
QT *= widgets

include("$${top_srcdir}/config.pri")

RC_FILE *= cot-version.rc

RESOURCES *= \
    resources/cot-resources.qrc

FORMS *= \
    updater/CUpdateDialog.ui \
    gui/widgets/CStatusWidget.ui \
    gui/panel/CPCDiagnosticTab.ui \
    gui/panel/CPCHistogramTab.ui \
    gui/panel/CPCMeasureTab.ui \
    gui/panel/CPCPlusTab.ui \
    gui/panel/CPCToolsTab.ui \
    gui/panel/CPCWindow.ui \
    gui/measure/CMeasureMeasureTab.ui \
    gui/measure/CMeasureStreamTab.ui \
    gui/measure/CMeasureWindow.ui \
    gui/tools/electrical-tests/CElectricalTests420Tab.ui \
    gui/tools/electrical-tests/CElectricalTestsActuatorTab.ui \
    gui/tools/electrical-tests/CElectricalTestsInputsTab.ui \
    gui/tools/electrical-tests/CElectricalTestsPumpsTab.ui \
    gui/tools/electrical-tests/CElectricalTestsRelaysTab.ui \
    gui/tools/electrical-tests/CElectricalTestsWindow.ui \
    gui/tools/options/COptionsWindow.ui \
    gui/tools/options/COptionsOptionsTab.ui \
    gui/tools/options/COptionsAutoCyclesTab.ui \
    gui/tools/options/COptionsSchedulerTab.ui \
    gui/tools/options/COptionsThresholdTab.ui \
    gui/tools/options/COptionsDateTimeTab.ui \
    gui/tools/log-files/CLogFilesWindow.ui \
    gui/tools/history/CHistoryWindow.ui \
    gui/tools/maintenance/CMaintenanceDiagnosticTab.ui \
    gui/tools/maintenance/CMaintenanceMaintenanceTab.ui \
    gui/tools/maintenance/CMaintenanceWindow.ui \
    gui/panel/CAboutWindow.ui \
    gui/tools/configurator/CConfiguratorWindow.ui \
    gui/tools/configurator/CConfiguratorCycleTab.ui \
    gui/tools/configurator/CConfiguratorActionsTab.ui \
    gui/tools/configurator/CConfiguratorVariablesTab.ui \
    gui/tools/configurator/CConfiguratorSequencerTab.ui \
    gui/tools/configurator/CConfiguratorStreamsTab.ui \
    gui/tools/configurator/CConfiguratorExtensionsTab.ui \
    gui/tools/configurator/CConfiguratorDisplayTab.ui \
    gui/tools/configurator/CConfiguratorHardwareTab.ui \
    gui/tools/configurator/CConfiguratorNetworkTab.ui \
    gui/tools/configurator/variables/CEditVariableWindow.ui \
    gui/widgets/CGenericItemSelector.ui



HEADERS *= \
    automate/CAutomate.h \
    automate/CConfigurationBackup.h \
    automate/CControlerAutomate.h \
    automate/CControlerCycle.h \
    automate/CDisplayConf.h \
    automate/CLinkAction.h \
    automate/CModelConfigFile.h \
    automate/CModelExtensionCard.h \
    automate/CRunnableCycle.h \
    automate/CSequenceur.h \
    automate/CStep.h \
    automate/INetwork.h \
    automate/IObserverAutomate.h \
    automate/IOrgan.h \
    automate/actions/CActionCmdPompe.h \
    automate/actions/CActionCmdReadInput.h \
    automate/actions/CActionCmdRelay.h \
    automate/actions/CActionFactory.h \
    automate/actions/CActionUnknow.h \
    automate/actions/IAction.h \
    automate/com/CComJBus.h \
    automate/com/ICom.h \
    automate/com/IComObserver.h \
    automate/cycles/CCycleAutonome.h \
    automate/cycles/CCycleFactory.h \
    automate/cycles/CCycleIO.h \
    automate/cycles/CCycleMaintenance.h \
    automate/cycles/CCycleMesure.h \
    automate/cycles/CCyclePause.h \
    automate/cycles/ICycle.h \
    automate/units/CConverterCoef.h \
    automate/units/CConverterCoefOffset.h \
    automate/units/CConverterOffset.h \
    automate/units/CConverterOffsetCoef.h \
    automate/units/CConverterFactory.h \
    automate/units/CConverterUnknow.h \
    automate/units/CUnit.h \
    automate/units/IConverter.h \
    automate/variables/CVariableBool.h \
    automate/variables/CVariableFactory.h \
    automate/variables/CVariableFloat.h \
    automate/variables/CVariableInputBool.h \
    automate/variables/CVariableInputFloat.h \
    automate/variables/CVariableInputInt.h \
    automate/variables/CVariableInt.h \
    automate/variables/CVariableOutputBool.h \
    automate/variables/CVariableOutputFloat.h \
    automate/variables/CVariableOutputInt.h \
    automate/variables/CVariableString.h \
    automate/variables/CVariableUnknow.h \
    automate/variables/CVariableVoie.h \
    automate/variables/IVariable.h \
    automate/variables/IVariableInput.h \
    automate/variables/IVariableOutput.h \
    keyboards/CKeyboardButtonBase.h \
    keyboards/CKeyboardDialog.h \
    keyboards/CKeyboardLayoutUtils.h \
    keyboards/CKeyboardNormalButton.h \
    keyboards/CKeyboardSpecialButton.h \
    keyboards/CKeyboardWidget.h \
    keyboards/CNumericalKeyboardDialog.h \
    keyboards/CNumericalKeyboardWidget.h \
    updater/CUpdateDialog.h \
    updater/CUpdateManager.h \
    gui/widgets/CGenericItemSelector.h \
    gui/widgets/CGenericListDelegate.h \
    gui/widgets/CGenericListModel.h \
    gui/widgets/CPushButton.h \
    gui/widgets/CScrollableWidget.h \
    gui/widgets/CStatusLabel.h \
    gui/widgets/CStatusWidget.h \
    gui/widgets/CToolButton.h \
    gui/widgets/CVerticalButtonBar.h \
    gui/panel/CAlarmsWindow.h \
    gui/panel/CPCDiagnosticTab.h \
    gui/panel/CPCHistogramTab.h \
    gui/panel/CPCMeasureTab.h \
    gui/panel/CPCPlusTab.h \
    gui/panel/CPCToolsTab.h \
    gui/panel/CPCWindow.h \
    gui/panel/IPCTab.h \
    gui/panel/IWindow.h \
    gui/measure/CMeasureMeasureTab.h \
    gui/measure/CMeasureStreamTab.h \
    gui/measure/CMeasureWindow.h \
    gui/measure/IMeasureTab.h \
    gui/tools/electrical-tests/CElectricalTests420Tab.h \
    gui/tools/electrical-tests/CElectricalTestsActuatorTab.h \
    gui/tools/electrical-tests/CElectricalTestsInputsTab.h \
    gui/tools/electrical-tests/CElectricalTestsPumpsTab.h \
    gui/tools/electrical-tests/CElectricalTestsRelaysTab.h \
    gui/tools/electrical-tests/CElectricalTestsWindow.h \
    gui/tools/electrical-tests/IElectricalTestsTab.h \
    gui/widgets/CLabelledToolButton.h \
    gui/widgets/CLedButton.h \
    gui/widgets/CSwitchButton.h \
    gui/tools/options/COptionsWindow.h \
    gui/tools/options/IOptionsTab.h \
    gui/tools/options/COptionsOptionsTab.h \
    gui/tools/options/COptionsAutoCyclesTab.h \
    gui/tools/options/COptionsSchedulerTab.h \
    gui/tools/options/COptionsThresholdTab.h \
    gui/tools/options/COptionsDateTimeTab.h \
    gui/tools/log-files/CLogFilesWindow.h \
    gui/tools/history/CHistoryWindow.h \
    gui/tools/maintenance/CMaintenanceDiagnosticTab.h \
    gui/tools/maintenance/CMaintenanceMaintenanceTab.h \
    gui/tools/maintenance/CMaintenanceWindow.h \
    gui/tools/maintenance/IMaintenanceTab.h \
    gui/IVariableMeasuresUIHandler.h \
    gui/IVariableUIHandler.h \
    $$KPLOTTING_SRC_PWD/src/kplotaxis.h \ 
    $$KPLOTTING_SRC_PWD/src/kplotobject.h \ 
    $$KPLOTTING_SRC_PWD/src/kplotpoint.h \
    $$KPLOTTING_SRC_PWD/src/kplotwidget.h \
    graphics/CGraphicsWidget.h \
    gui/IVariableMaintenanceUIHandler.h \
    gui/widgets/CLabelledToolButtonGrid.h \
    gui/panel/CAboutWindow.h \
    gui/widgets/CMessageBox.h \
    gui/tools/configurator/CConfiguratorWindow.h \
    gui/tools/configurator/IConfiguratorTab.h \
    gui/tools/configurator/CConfiguratorCycleTab.h \
    gui/tools/configurator/CConfiguratorActionsTab.h \
    gui/tools/configurator/CConfiguratorVariablesTab.h \
    gui/tools/configurator/CConfiguratorSequencerTab.h \
    gui/tools/configurator/CConfiguratorStreamsTab.h \
    gui/tools/configurator/CConfiguratorExtensionsTab.h \
    gui/tools/configurator/CConfiguratorDisplayTab.h \
    gui/tools/configurator/CConfiguratorHardwareTab.h \
    gui/tools/configurator/CConfiguratorNetworkTab.h \
    gui/tools/configurator/variables/CEditVariableWindow.h \
	gui/widgets/CGenericVariableUIHandler.h \
	gui/ConfiguratorUIHandler.h

SOURCES *= \
    automate/CAutomate.cpp \
    automate/CConfigurationBackup.cpp \
    automate/CControlerAutomate.cpp \
    automate/CControlerCycle.cpp \
    automate/CDisplayConf.cpp \
    automate/CLinkAction.cpp \
    automate/CModelConfigFile.cpp \
    automate/CModelExtensionCard.cpp \
    automate/CRunnableCycle.cpp \
    automate/CSequenceur.cpp \
    automate/CStep.cpp \
    automate/INetwork.cpp \
    automate/IObserverAutomate.cpp \
    automate/IOrgan.cpp \
    automate/actions/CActionCmdPompe.cpp \
    automate/actions/CActionCmdReadInput.cpp \
    automate/actions/CActionCmdRelay.cpp \
    automate/actions/CActionFactory.cpp \
    automate/actions/CActionUnknow.cpp \
    automate/actions/IAction.cpp \
    automate/com/CComJBus.cpp \
    automate/com/ICom.cpp \
    automate/com/IComObserver.cpp \
    automate/cycles/CCycleAutonome.cpp \
    automate/cycles/CCycleFactory.cpp \
    automate/cycles/CCycleIO.cpp \
    automate/cycles/CCycleMaintenance.cpp \
    automate/cycles/CCycleMesure.cpp \
    automate/cycles/CCyclePause.cpp \
    automate/cycles/ICycle.cpp \
    automate/units/CConverterCoef.cpp \
    automate/units/CConverterCoefOffset.cpp \
    automate/units/CConverterOffset.cpp \
    automate/units/CConverterOffsetCoef.cpp \
    automate/units/CConverterFactory.cpp \
    automate/units/CConverterUnknow.cpp \
    automate/units/CUnit.cpp \
    automate/units/IConverter.cpp \
    automate/variables/CVariableBool.cpp \
    automate/variables/CVariableFactory.cpp \
    automate/variables/CVariableFloat.cpp \
    automate/variables/CVariableInputBool.cpp \
    automate/variables/CVariableInputFloat.cpp \
    automate/variables/CVariableInputInt.cpp \
    automate/variables/CVariableInt.cpp \
    automate/variables/CVariableOutputBool.cpp \
    automate/variables/CVariableOutputFloat.cpp \
    automate/variables/CVariableOutputInt.cpp \
    automate/variables/CVariableString.cpp \
    automate/variables/CVariableUnknow.cpp \
    automate/variables/CVariableVoie.cpp \
    automate/variables/IVariable.cpp \
    automate/variables/IVariableInput.cpp \
    automate/variables/IVariableOuput.cpp \
    keyboards/CKeyboardButtonBase.cpp \
    keyboards/CKeyboardDialog.cpp \
    keyboards/CKeyboardLayoutUtils.cpp \
    keyboards/CKeyboardNormalButton.cpp \
    keyboards/CKeyboardSpecialButton.cpp \
    keyboards/CKeyboardWidget.cpp \
    keyboards/CNumericalKeyboardDialog.cpp \
    keyboards/CNumericalKeyboardWidget.cpp \
    updater/CUpdateDialog.cpp \
    updater/CUpdateManager.cpp \
    gui/widgets/CGenericItemSelector.cpp \
    gui/widgets/CGenericListDelegate.cpp \
    gui/widgets/CGenericListModel.cpp \
    gui/widgets/CLabelledToolButton.cpp \
    gui/widgets/CPushButton.cpp \
    gui/widgets/CScrollableWidget.cpp \
    gui/widgets/CStatusLabel.cpp \
    gui/widgets/CStatusWidget.cpp \
    gui/widgets/CToolButton.cpp \
    gui/widgets/CVerticalButtonBar.cpp \
    gui/panel/CAlarmsWindow.cpp \
    gui/panel/CPCDiagnosticTab.cpp \
    gui/panel/CPCHistogramTab.cpp \
    gui/panel/CPCMeasureTab.cpp \
    gui/panel/CPCPlusTab.cpp \
    gui/panel/CPCToolsTab.cpp \
    gui/panel/CPCWindow.cpp \
    gui/panel/IWindow.cpp \
    gui/measure/CMeasureMeasureTab.cpp \
    gui/measure/CMeasureStreamTab.cpp \
    gui/measure/CMeasureWindow.cpp \
    gui/tools/electrical-tests/CElectricalTests420Tab.cpp \
    gui/tools/electrical-tests/CElectricalTestsActuatorTab.cpp \
    gui/tools/electrical-tests/CElectricalTestsInputsTab.cpp \
    gui/tools/electrical-tests/CElectricalTestsPumpsTab.cpp \
    gui/tools/electrical-tests/CElectricalTestsRelaysTab.cpp \
    gui/tools/electrical-tests/CElectricalTestsWindow.cpp \
    gui/widgets/CSwitchButton.cpp \
    gui/widgets/CLedButton.cpp \
    gui/tools/options/COptionsWindow.cpp \
    gui/tools/options/COptionsOptionsTab.cpp \
    gui/tools/options/COptionsAutoCyclesTab.cpp \
    gui/tools/options/COptionsSchedulerTab.cpp \
    gui/tools/options/COptionsThresholdTab.cpp \
    gui/tools/options/COptionsDateTimeTab.cpp \
    gui/tools/log-files/CLogFilesWindow.cpp \
    gui/tools/history/CHistoryWindow.cpp \
    gui/tools/maintenance/CMaintenanceDiagnosticTab.cpp \
    gui/tools/maintenance/CMaintenanceMaintenanceTab.cpp \
    gui/tools/maintenance/CMaintenanceWindow.cpp \
    gui/IVariableMeasuresUIHandler.cpp \
    gui/IVariableUIHandler.cpp \
    $$KPLOTTING_SRC_PWD/src/kplotaxis.cpp \ 
    $$KPLOTTING_SRC_PWD/src/kplotobject.cpp \ 
    $$KPLOTTING_SRC_PWD/src/kplotpoint.cpp \
    $$KPLOTTING_SRC_PWD/src/kplotwidget.cpp \
    graphics/CGraphicsWidget.cpp \
    gui/IVariableMaintenanceUIHandler.cpp \
    gui/widgets/CLabelledToolButtonGrid.cpp \
    gui/panel/CAboutWindow.cpp \
    gui/widgets/CMessageBox.cpp \
    gui/tools/configurator/CConfiguratorWindow.cpp \
    gui/tools/configurator/CConfiguratorCycleTab.cpp \
    gui/tools/configurator/CConfiguratorActionsTab.cpp \
    gui/tools/configurator/CConfiguratorVariablesTab.cpp \
    gui/tools/configurator/CConfiguratorSequencerTab.cpp \
    gui/tools/configurator/CConfiguratorStreamsTab.cpp \
    gui/tools/configurator/CConfiguratorExtensionsTab.cpp \
    gui/tools/configurator/CConfiguratorDisplayTab.cpp \
    gui/tools/configurator/CConfiguratorHardwareTab.cpp \
    gui/tools/configurator/CConfiguratorNetworkTab.cpp \
    gui/tools/configurator/variables/CEditVariableWindow.cpp \
	gui/widgets/CGenericVariableUIHandler.cpp \
    gui/ConfiguratorUIHandler.cpp \
