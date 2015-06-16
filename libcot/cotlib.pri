# This is a separate .pri file for the Qt-MSVC integration
# Do not add any DEFINES here, MSVC will just ignore them.
# Only list source files here.

RC_FILE *= cot-version.rc

RESOURCES *= \
    resources/cot-resources.qrc

FORMS *= \
    updater/CUpdateDialog.ui \
    keyboards/CKeyboardDialog.ui \
    gui/widgets/CStatusWidget.ui \
    gui/panel/CAlarmsWindow.ui \
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
    gui/tools/options/COptionsThresholdTab.ui \
    gui/tools/options/COptionsDateTimeTab.ui \
    gui/tools/log-files/CLogFilesWindow.ui \
    gui/tools/history/CHistoryWindow.ui \
    gui/tools/maintenance/CMaintenanceDiagnosticTab.ui \
    gui/tools/maintenance/CMaintenanceMaintenanceTab.ui \
    gui/tools/maintenance/CMaintenanceWindow.ui \
    gui/tools/configurator/CConfiguratorWindow.ui \
    gui/tools/configurator/IConfiguratorEditWindow.ui

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
    automate/CSequencer.h \
    automate/CStep.h \
    automate/IOrgan.h \
    automate/actions/CActionCmdPompe.h \
    automate/actions/CActionCmdReadInput.h \
    automate/actions/CActionCmdRelay.h \
    automate/actions/CActionBlock.h \
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
    automate/variables/CVariableStream.h \
    automate/variables/CVariableMeasure.h \
    automate/variables/IVariable.h \
    automate/variables/IVariableInput.h \
    automate/variables/IVariableOutput.h \
    automate/variables/CVariableMutable.h \
    automate/organs/COrgan.h \
    #automate/organs/CCOrganFactory.h \
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
    gui/widgets/CScrollablePagerWidget.h \
    gui/widgets/CScrollablePlainTextEdit.h \
    gui/widgets/CStatusLabel.h \
    gui/widgets/CStatusWidget.h \
    gui/widgets/CToolButton.h \
    gui/widgets/CVerticalButtonBar.h \
    gui/widgets/CLabelledToolButton.h \
    gui/widgets/CLedButton.h \
    gui/widgets/CSwitchButton.h \
    gui/widgets/CLabelledToolButtonGrid.h \
    gui/widgets/CMessageBox.h \
    gui/widgets/CDialog.h \
    gui/widgets/CStepWidget.h \
    gui/widgets/CGenericVariablesEditor.h \
    gui/widgets/CGenericVariablesEditorWindow.h \
    gui/widgets/CGenericVariablesUIHandler.h \
    gui/widgets/CProxyStyle.h \
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
    gui/tools/options/COptionsWindow.h \
    gui/tools/options/IOptionsTab.h \
    gui/tools/options/COptionsOptionsTab.h \
    gui/tools/options/COptionsAutoCyclesTab.h \
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
    gui/IVariableObjectDescriber.h \
    gui/IConfiguratorUIHandler.h \
    $$KPLOTTING_SRC_PWD/src/kplotaxis.h \
    $$KPLOTTING_SRC_PWD/src/kplotobject.h \
    $$KPLOTTING_SRC_PWD/src/kplotpoint.h \
    $$KPLOTTING_SRC_PWD/src/kplotwidget.h \
    graphics/CGraphicsWidget.h \
    gui/IVariableMaintenanceUIHandler.h \
    gui/panel/CAboutWindow.h \
    automate/variables/CVariableOutputListVariables.h \
    automate/com/CComFactory.h \
    automate/com/CComUnknow.h \
    automate/cotautomate_debug.h \
    gui/cotgui_debug.h \
    gui/tools/configurator/CConfiguratorWindow.h \
    gui/tools/configurator/IConfiguratorTab.h \
    gui/tools/configurator/actions/CConfiguratorActionsTab.h \
    gui/tools/configurator/actions/CEditActionTab.h \
    gui/tools/configurator/actions/CEditActionTabUIHandler.h \
    gui/tools/configurator/actions/CEditActionWindow.h \
    gui/tools/configurator/actions/ConfiguratorActionsUIHandler.h \
    gui/tools/configurator/cycles/CConfiguratorCycleTab.h \
    gui/tools/configurator/cycles/CConfiguratorCycleTabUIHandler.h \
    gui/tools/configurator/cycles/CEditCycleTab.h \
    gui/tools/configurator/cycles/CEditCycleTabUIHandler.h \
    gui/tools/configurator/cycles/CEditCycleWindow.h \
    gui/tools/configurator/display/CConfiguratorDisplayTab.h \
    gui/tools/configurator/extensions/CConfiguratorExtensionsTab.h \
    gui/tools/configurator/extensions/CEditComTab.h \
    gui/tools/configurator/extensions/CEditExtensionWindow.h \
    gui/tools/configurator/extensions/CEditGeneralTab.h \
    gui/tools/configurator/extensions/CEditOrgansTab.h \
    gui/tools/configurator/hardware/CConfiguratorHardwareTab.h \
    gui/tools/configurator/network/CConfiguratorNetworkTab.h \
    gui/tools/configurator/sequencer/CConfiguratorSequencerTab.h \
    gui/tools/configurator/sequencer/ConfiguratorSequencerUIHandler.h \
    gui/tools/configurator/streams/CConfiguratorStreamsTab.h \
    gui/tools/configurator/streams/ConfiguratorStreamsUIHandler.h \
    gui/tools/configurator/variables/CConfiguratorVariablesTab.h \
    gui/tools/configurator/variables/CEditInBindsTab.h \
    gui/tools/configurator/variables/CEditInBindsUIHandler.h \
    gui/tools/configurator/variables/CEditOutBindsTab.h \
    gui/tools/configurator/variables/CEditOutBindsUIHandler.h \
    gui/tools/configurator/variables/CEditVariableTab.h \
    gui/tools/configurator/variables/CEditVariableTabUIHandler.h \
    gui/tools/configurator/variables/CEditVariableWindow.h \
    gui/tools/configurator/variables/ConfiguratorVariablesUIHandler.h \
    gui/IScrollableUIWidget.h \
    gui/tools/configurator/IConfiguratorEditWindow.h \
    gui/tools/configurator/IConfiguratorEditTab.h \
    gui/tools/configurator/steps/CStepWidgetUIHandler.h \
    gui/tools/configurator/steps/CEditStepListTab.h \
    gui/StyleRepository.h

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
    automate/CSequencer.cpp \
    automate/CStep.cpp \
    automate/IOrgan.cpp \
    automate/actions/CActionCmdPompe.cpp \
    automate/actions/CActionCmdReadInput.cpp \
    automate/actions/CActionCmdRelay.cpp \
    automate/actions/CActionBlock.cpp \
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
    automate/variables/CVariableStream.cpp \
    automate/variables/CVariableMeasure.cpp \
    automate/variables/IVariable.cpp \
    automate/variables/IVariableInput.cpp \
    automate/variables/IVariableOuput.cpp \
    automate/variables/CVariableMutable.cpp \
    automate/organs/COrgan.cpp \
    automate/organs/COrganFactory.cpp \
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
    gui/widgets/CScrollablePlainTextEdit.cpp \
    gui/widgets/CStatusLabel.cpp \
    gui/widgets/CStatusWidget.cpp \
    gui/widgets/CToolButton.cpp \
    gui/widgets/CVerticalButtonBar.cpp \
    gui/widgets/CSwitchButton.cpp \
    gui/widgets/CLedButton.cpp \
    gui/widgets/CLabelledToolButtonGrid.cpp \
    gui/widgets/CMessageBox.cpp \
    gui/widgets/CDialog.cpp \
    gui/widgets/CStepWidget.cpp \
    gui/widgets/CGenericVariablesEditor.cpp \
    gui/widgets/CGenericVariablesEditorWindow.cpp \
    gui/widgets/CGenericVariablesUIHandler.cpp \
    gui/widgets/CScrollablePagerWidget.cpp \
    gui/widgets/CProxyStyle.cpp \
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
    gui/tools/options/COptionsWindow.cpp \
    gui/tools/options/COptionsOptionsTab.cpp \
    gui/tools/options/COptionsAutoCyclesTab.cpp \
    gui/tools/options/COptionsThresholdTab.cpp \
    gui/tools/options/COptionsDateTimeTab.cpp \
    gui/tools/log-files/CLogFilesWindow.cpp \
    gui/tools/history/CHistoryWindow.cpp \
    gui/tools/maintenance/CMaintenanceDiagnosticTab.cpp \
    gui/tools/maintenance/CMaintenanceMaintenanceTab.cpp \
    gui/tools/maintenance/CMaintenanceWindow.cpp \
    gui/IVariableMeasuresUIHandler.cpp \
    gui/IVariableUIHandler.cpp \
    gui/IVariableObjectDescriber.cpp \
    gui/IConfiguratorUIHandler.cpp \
    $$KPLOTTING_SRC_PWD/src/kplotaxis.cpp \
    $$KPLOTTING_SRC_PWD/src/kplotobject.cpp \
    $$KPLOTTING_SRC_PWD/src/kplotpoint.cpp \
    $$KPLOTTING_SRC_PWD/src/kplotwidget.cpp \
    graphics/CGraphicsWidget.cpp \
    gui/IVariableMaintenanceUIHandler.cpp \
    gui/panel/CAboutWindow.cpp \
    automate/variables/CVariableOutputListVariables.cpp \
    automate/com/CComFactory.cpp \
    automate/com/CComUnknow.cpp \
    automate/cotautomate_debug.cpp \
    gui/cotgui_debug.cpp \
    gui/tools/configurator/CConfiguratorWindow.cpp \
    gui/tools/configurator/actions/CConfiguratorActionsTab.cpp \
    gui/tools/configurator/actions/CEditActionTab.cpp \
    gui/tools/configurator/actions/CEditActionTabUIHandler.cpp \
    gui/tools/configurator/actions/CEditActionWindow.cpp \
    gui/tools/configurator/actions/ConfiguratorActionsUIHandler.cpp \
    gui/tools/configurator/cycles/CConfiguratorCycleTab.cpp \
    gui/tools/configurator/cycles/CConfiguratorCycleTabUIHandler.cpp \
    gui/tools/configurator/cycles/CEditCycleTab.cpp \
    gui/tools/configurator/cycles/CEditCycleTabUIHandler.cpp \
    gui/tools/configurator/cycles/CEditCycleWindow.cpp \
    gui/tools/configurator/display/CConfiguratorDisplayTab.cpp \
    gui/tools/configurator/extensions/CConfiguratorExtensionsTab.cpp \
    gui/tools/configurator/extensions/CEditComTab.cpp \
    gui/tools/configurator/extensions/CEditExtensionWindow.cpp \
    gui/tools/configurator/extensions/CEditGeneralTab.cpp \
    gui/tools/configurator/extensions/CEditOrgansTab.cpp \
    gui/tools/configurator/hardware/CConfiguratorHardwareTab.cpp \
    gui/tools/configurator/network/CConfiguratorNetworkTab.cpp \
    gui/tools/configurator/sequencer/CConfiguratorSequencerTab.cpp \
    gui/tools/configurator/sequencer/ConfiguratorSequencerUIHandler.cpp \
    gui/tools/configurator/streams/CConfiguratorStreamsTab.cpp \
    gui/tools/configurator/streams/ConfiguratorStreamsUIHandler.cpp \
    gui/tools/configurator/variables/CConfiguratorVariablesTab.cpp \
    gui/tools/configurator/variables/CEditInBindsTab.cpp \
    gui/tools/configurator/variables/CEditInBindsUIHandler.cpp \
    gui/tools/configurator/variables/CEditOutBindsTab.cpp \
    gui/tools/configurator/variables/CEditOutBindsUIHandler.cpp \
    gui/tools/configurator/variables/CEditVariableTab.cpp \
    gui/tools/configurator/variables/CEditVariableTabUIHandler.cpp \
    gui/tools/configurator/variables/CEditVariableWindow.cpp \
    gui/tools/configurator/variables/ConfiguratorVariablesUIHandler.cpp \
    gui/IScrollableUIWidget.cpp \
    gui/tools/configurator/IConfiguratorEditWindow.cpp \
    gui/tools/configurator/steps/CStepWidgetUIHandler.cpp \
    gui/tools/configurator/steps/CEditStepListTab.cpp \
    gui/StyleRepository.cpp
