# This is a separate .pri file for the Qt-MSVC integration
# Do not add any DEFINES here, MSVC will just ignore them.
# Only list source files here.

RC_FILE *= $$PWD/cot-version.rc

RESOURCES *= \
    $$PWD/resources/cot-resources.qrc

FORMS *= \
    $$PWD/updater/CUpdateDialog.ui \
    $$PWD/keyboards/CKeyboardDialog.ui \
    $$PWD/gui/widgets/CStatusWidget.ui \
    $$PWD/gui/panel/CAlarmsWindow.ui \
    $$PWD/gui/panel/CPCDiagnosticTab.ui \
    $$PWD/gui/panel/CPCHistogramTab.ui \
    $$PWD/gui/panel/CPCMeasureTab.ui \
    $$PWD/gui/panel/CPCPlusTab.ui \
    $$PWD/gui/panel/CPCToolsTab.ui \
    $$PWD/gui/panel/CPCWindow.ui \
    $$PWD/gui/measure/CMeasureMeasureTab.ui \
    $$PWD/gui/measure/CMeasureStreamTab.ui \
    $$PWD/gui/measure/CMeasureWindow.ui \
    $$PWD/gui/tools/electrical-tests/CElectricalTests420Tab.ui \
    $$PWD/gui/tools/electrical-tests/CElectricalTestsActuatorTab.ui \
    $$PWD/gui/tools/electrical-tests/CElectricalTestsInputsTab.ui \
    $$PWD/gui/tools/electrical-tests/CElectricalTestsPumpsTab.ui \
    $$PWD/gui/tools/electrical-tests/CElectricalTestsRelaysTab.ui \
    $$PWD/gui/tools/electrical-tests/CElectricalTestsWindow.ui \
    $$PWD/gui/tools/options/COptionsWindow.ui \
    $$PWD/gui/tools/options/COptionsOptionsTab.ui \
    $$PWD/gui/tools/options/COptionsAutoCyclesTab.ui \
    $$PWD/gui/tools/options/COptionsThresholdTab.ui \
    $$PWD/gui/tools/options/COptionsDateTimeTab.ui \
    $$PWD/gui/tools/history/CHistoryWindow.ui \
    $$PWD/gui/tools/maintenance/CMaintenanceDiagnosticTab.ui \
    $$PWD/gui/tools/maintenance/CMaintenanceMaintenanceTab.ui \
    $$PWD/gui/tools/maintenance/CMaintenanceWindow.ui \
    $$PWD/gui/tools/configurator/CConfiguratorWindow.ui \
    $$PWD/gui/tools/configurator/IConfiguratorEditWindow.ui \
    $$PWD/gui/tools/electrical-tests/CElectricalTestsSolenoidsTab.ui

HEADERS *= \
    $$PWD/automate/CAutomate.h \
    $$PWD/automate/CConfigurationBackup.h \
    $$PWD/automate/CControlerAutomate.h \
    $$PWD/automate/CControlerCycle.h \
    $$PWD/automate/CDisplayConf.h \
    $$PWD/automate/CLinkAction.h \
    $$PWD/automate/CModelConfigFile.h \
    $$PWD/automate/CModelExtensionCard.h \
    $$PWD/automate/CRunnableCycle.h \
    $$PWD/automate/CStep.h \
    $$PWD/automate/IOrgan.h \
    $$PWD/automate/actions/CActionCmdPompe.h \
    $$PWD/automate/actions/CActionCmdReadInput.h \
    $$PWD/automate/actions/CActionBlock.h \
    $$PWD/automate/actions/CActionFactory.h \
    $$PWD/automate/actions/CActionUnknow.h \
    $$PWD/automate/actions/IAction.h \
    $$PWD/automate/com/CComJBus.h \
    $$PWD/automate/com/ICom.h \
    $$PWD/automate/com/IComObserver.h \
    $$PWD/automate/cycles/CCycleAutonome.h \
    $$PWD/automate/cycles/CCycleFactory.h \
    $$PWD/automate/cycles/CCycleMaintenance.h \
    $$PWD/automate/cycles/CCycleMesure.h \
    $$PWD/automate/cycles/CCyclePause.h \
    $$PWD/automate/cycles/ICycle.h \
    $$PWD/automate/units/CConverterCoef.h \
    $$PWD/automate/units/CConverterCoefOffset.h \
    $$PWD/automate/units/CConverterOffset.h \
    $$PWD/automate/units/CConverterOffsetCoef.h \
    $$PWD/automate/units/CConverterFactory.h \
    $$PWD/automate/units/CConverterUnknow.h \
    $$PWD/automate/units/CUnit.h \
    $$PWD/automate/units/IConverter.h \
    $$PWD/automate/variables/CVariableBool.h \
    $$PWD/automate/variables/CVariableFactory.h \
    $$PWD/automate/variables/CVariableFloat.h \
    $$PWD/automate/variables/CVariableInputBool.h \
    $$PWD/automate/variables/CVariableInputFloat.h \
    $$PWD/automate/variables/CVariableInputInt.h \
    $$PWD/automate/variables/CVariableInt.h \
    $$PWD/automate/variables/CVariableOutputBool.h \
    $$PWD/automate/variables/CVariableOutputFloat.h \
    $$PWD/automate/variables/CVariableOutputInt.h \
    $$PWD/automate/variables/CVariableString.h \
    $$PWD/automate/variables/CVariableUnknow.h \
    $$PWD/automate/variables/CVariableStream.h \
    $$PWD/automate/variables/CVariableMeasure.h \
    $$PWD/automate/variables/IVariable.h \
    $$PWD/automate/variables/IVariableInput.h \
    $$PWD/automate/variables/IVariableOutput.h \
    $$PWD/automate/variables/CVariableMutable.h \
    $$PWD/automate/organs/COrgan.h \
    #$$PWD/automate/organs/CCOrganFactory.h \
    $$PWD/keyboards/CKeyboardButtonBase.h \
    $$PWD/keyboards/CKeyboardDialog.h \
    $$PWD/keyboards/CKeyboardLayoutUtils.h \
    $$PWD/keyboards/CKeyboardNormalButton.h \
    $$PWD/keyboards/CKeyboardSpecialButton.h \
    $$PWD/keyboards/CKeyboardWidget.h \
    $$PWD/keyboards/CNumericalKeyboardDialog.h \
    $$PWD/keyboards/CNumericalKeyboardWidget.h \
    $$PWD/updater/CUpdateDialog.h \
    $$PWD/updater/CUpdateManager.h \
    $$PWD/gui/widgets/CGenericItemSelector.h \
    $$PWD/gui/widgets/CGenericListDelegate.h \
    $$PWD/gui/widgets/CGenericListModel.h \
    $$PWD/gui/widgets/CPushButton.h \
    $$PWD/gui/widgets/CScrollableWidget.h \
    $$PWD/gui/widgets/CScrollablePagerWidget.h \
    $$PWD/gui/widgets/CScrollablePlainTextEdit.h \
    $$PWD/gui/widgets/CStatusLabel.h \
    $$PWD/gui/widgets/CStatusWidget.h \
    $$PWD/gui/widgets/CToolButton.h \
    $$PWD/gui/widgets/CVerticalButtonBar.h \
    $$PWD/gui/widgets/CLabelledToolButton.h \
    $$PWD/gui/widgets/CLedButton.h \
    $$PWD/gui/widgets/CSwitchButton.h \
    $$PWD/gui/widgets/CLabelledToolButtonGrid.h \
    $$PWD/gui/widgets/CMessageBox.h \
    $$PWD/gui/widgets/CDialog.h \
    $$PWD/gui/widgets/CStepWidget.h \
    $$PWD/gui/widgets/CGenericVariablesEditor.h \
    $$PWD/gui/widgets/CGenericVariablesEditorWindow.h \
    $$PWD/gui/widgets/CGenericVariablesUIHandler.h \
    $$PWD/gui/widgets/CProxyStyle.h \
    $$PWD/gui/panel/CAlarmsWindow.h \
    $$PWD/gui/panel/CPCDiagnosticTab.h \
    $$PWD/gui/panel/CPCHistogramTab.h \
    $$PWD/gui/panel/CPCMeasureTab.h \
    $$PWD/gui/panel/CPCPlusTab.h \
    $$PWD/gui/panel/CPCToolsTab.h \
    $$PWD/gui/panel/CPCWindow.h \
    $$PWD/gui/panel/IPCTab.h \
    $$PWD/gui/panel/IWindow.h \
    $$PWD/gui/measure/CMeasureMeasureTab.h \
    $$PWD/gui/measure/CMeasureStreamTab.h \
    $$PWD/gui/measure/CMeasureWindow.h \
    $$PWD/gui/measure/IMeasureTab.h \
    $$PWD/gui/tools/electrical-tests/CElectricalTests420Tab.h \
    $$PWD/gui/tools/electrical-tests/CElectricalTestsActuatorTab.h \
    $$PWD/gui/tools/electrical-tests/CElectricalTestsInputsTab.h \
    $$PWD/gui/tools/electrical-tests/CElectricalTestsPumpsTab.h \
    $$PWD/gui/tools/electrical-tests/CElectricalTestsRelaysTab.h \
    $$PWD/gui/tools/electrical-tests/CElectricalTestsWindow.h \
    $$PWD/gui/tools/electrical-tests/IElectricalTestsTab.h \
    $$PWD/gui/tools/options/COptionsWindow.h \
    $$PWD/gui/tools/options/IOptionsTab.h \
    $$PWD/gui/tools/options/COptionsOptionsTab.h \
    $$PWD/gui/tools/options/COptionsAutoCyclesTab.h \
    $$PWD/gui/tools/options/COptionsThresholdTab.h \
    $$PWD/gui/tools/options/COptionsDateTimeTab.h \
    $$PWD/gui/tools/log-files/CLogFilesWindow.h \
    $$PWD/gui/tools/history/CHistoryWindow.h \
    $$PWD/gui/tools/maintenance/CMaintenanceDiagnosticTab.h \
    $$PWD/gui/tools/maintenance/CMaintenanceMaintenanceTab.h \
    $$PWD/gui/tools/maintenance/CMaintenanceWindow.h \
    $$PWD/gui/tools/maintenance/IMaintenanceTab.h \
    $$PWD/gui/IVariableMeasuresUIHandler.h \
    $$PWD/gui/IVariableUIHandler.h \
    $$PWD/gui/IVariableObjectDescriber.h \
    $$PWD/gui/IConfiguratorUIHandler.h \
    $$KPLOTTING_SRC_PWD/src/kplotaxis.h \
    $$KPLOTTING_SRC_PWD/src/kplotobject.h \
    $$KPLOTTING_SRC_PWD/src/kplotpoint.h \
    $$KPLOTTING_SRC_PWD/src/kplotwidget.h \
    $$PWD/graphics/CGraphicsWidget.h \
    $$PWD/graphics/CPlotObject.h \
    $$PWD/gui/IVariableMaintenanceUIHandler.h \
    $$PWD/gui/panel/CAboutWindow.h \
    $$PWD/automate/variables/CVariableOutputListVariables.h \
    $$PWD/automate/com/CComFactory.h \
    $$PWD/automate/com/CComUnknow.h \
    $$PWD/automate/cotautomate_debug.h \
    $$PWD/gui/cotgui_debug.h \
    $$PWD/gui/tools/configurator/CConfiguratorWindow.h \
    $$PWD/gui/tools/configurator/IConfiguratorTab.h \
    $$PWD/gui/tools/configurator/actions/CConfiguratorActionsTab.h \
    $$PWD/gui/tools/configurator/actions/CEditActionTab.h \
    $$PWD/gui/tools/configurator/actions/CEditActionTabUIHandler.h \
    $$PWD/gui/tools/configurator/actions/CEditActionWindow.h \
    $$PWD/gui/tools/configurator/actions/ConfiguratorActionsUIHandler.h \
    $$PWD/gui/tools/configurator/cycles/CConfiguratorCycleTab.h \
    $$PWD/gui/tools/configurator/cycles/CConfiguratorCycleTabUIHandler.h \
    $$PWD/gui/tools/configurator/cycles/CEditCycleTab.h \
    $$PWD/gui/tools/configurator/cycles/CEditCycleTabUIHandler.h \
    $$PWD/gui/tools/configurator/cycles/CEditCycleWindow.h \
    $$PWD/gui/tools/configurator/display/CConfiguratorDisplayTab.h \
    $$PWD/gui/tools/configurator/extensions/CConfiguratorExtensionsTab.h \
    $$PWD/gui/tools/configurator/extensions/CEditComTab.h \
    $$PWD/gui/tools/configurator/extensions/CEditExtensionWindow.h \
    $$PWD/gui/tools/configurator/extensions/CEditGeneralTab.h \
    $$PWD/gui/tools/configurator/extensions/CEditOrgansTab.h \
    $$PWD/gui/tools/configurator/hardware/CConfiguratorHardwareTab.h \
    $$PWD/gui/tools/configurator/network/CConfiguratorNetworkTab.h \
    $$PWD/gui/tools/configurator/sequencer/CConfiguratorSequencerTab.h \
    $$PWD/gui/tools/configurator/sequencer/ConfiguratorSequencerUIHandler.h \
    $$PWD/gui/tools/configurator/streams/CConfiguratorStreamsTab.h \
    $$PWD/gui/tools/configurator/streams/ConfiguratorStreamsUIHandler.h \
    $$PWD/gui/tools/configurator/variables/CConfiguratorVariablesTab.h \
    $$PWD/gui/tools/configurator/variables/CEditInBindsTab.h \
    $$PWD/gui/tools/configurator/variables/CEditInBindsUIHandler.h \
    $$PWD/gui/tools/configurator/variables/CEditOutBindsTab.h \
    $$PWD/gui/tools/configurator/variables/CEditOutBindsUIHandler.h \
    $$PWD/gui/tools/configurator/variables/CEditVariableTab.h \
    $$PWD/gui/tools/configurator/variables/CEditVariableTabUIHandler.h \
    $$PWD/gui/tools/configurator/variables/CEditVariableWindow.h \
    $$PWD/gui/tools/configurator/variables/ConfiguratorVariablesUIHandler.h \
    $$PWD/gui/IScrollableUIWidget.h \
    $$PWD/gui/IScrollablePlainTextEdit.h \
    $$PWD/gui/tools/configurator/IConfiguratorEditWindow.h \
    $$PWD/gui/tools/configurator/IConfiguratorEditTab.h \
    $$PWD/gui/tools/configurator/steps/CStepWidgetUIHandler.h \
    $$PWD/gui/tools/configurator/steps/CEditStepListTab.h \
    $$PWD/gui/StyleRepository.h \
    $$PWD/automate/actions/CActionCmdDigitalOutput.h \
    $$PWD/automate/actions/CActionTest.h \
    $$PWD/automate/CScheduler.h \
    $$PWD/automate/actions/CActionAcquisitionCitNpoc.h \
    $$PWD/automate/actions/CActionDCEngine.h \
    $$PWD/automate/actions/CActionRewriteOutput.h \
    $$PWD/automate/CThreadDiag.h \
    $$PWD/gui/widgets/CClickableLabel.h\
    $$PWD/automate/units/CConverterCrossProduct.h \
    $$PWD/gui/tools/initial-tests/CInitialTestWindow.h \
    $$PWD/gui/widgets/CDialogMaintenance.h \
    $$PWD/automate/actions/CActionCalibrationCalcul.h \
    $$PWD/automate/variables/CVariableAlarm.h \
    $$PWD/automate/actions/CActionCmd420.h \
    $$PWD/gui/tools/screenshot/CDialogScreenShots.h \
    $$PWD/automate/actions/CActionSum.h \
    $$PWD/automate/actions/CActionFindClosestFromReference.h \
    $$PWD/automate/actions/CActionFindBiggerValue.h \
    $$PWD/gui/tools/electrical-tests/CElectricalTestsSolenoidsTab.h

SOURCES *= \
    $$PWD/automate/CAutomate.cpp \
    $$PWD/automate/CConfigurationBackup.cpp \
    $$PWD/automate/CControlerAutomate.cpp \
    $$PWD/automate/CControlerCycle.cpp \
    $$PWD/automate/CDisplayConf.cpp \
    $$PWD/automate/CLinkAction.cpp \
    $$PWD/automate/CModelConfigFile.cpp \
    $$PWD/automate/CModelExtensionCard.cpp \
    $$PWD/automate/CRunnableCycle.cpp \
    $$PWD/automate/CStep.cpp \
    $$PWD/automate/IOrgan.cpp \
    $$PWD/automate/actions/CActionCmdPompe.cpp \
    $$PWD/automate/actions/CActionCmdReadInput.cpp \
    $$PWD/automate/actions/CActionBlock.cpp \
    $$PWD/automate/actions/CActionFactory.cpp \
    $$PWD/automate/actions/CActionUnknow.cpp \
    $$PWD/automate/actions/IAction.cpp \
    $$PWD/automate/com/CComJBus.cpp \
    $$PWD/automate/com/ICom.cpp \
    $$PWD/automate/com/IComObserver.cpp \
    $$PWD/automate/cycles/CCycleAutonome.cpp \
    $$PWD/automate/cycles/CCycleFactory.cpp \
    $$PWD/automate/cycles/CCycleMaintenance.cpp \
    $$PWD/automate/cycles/CCycleMesure.cpp \
    $$PWD/automate/cycles/CCyclePause.cpp \
    $$PWD/automate/cycles/ICycle.cpp \
    $$PWD/automate/units/CConverterCoef.cpp \
    $$PWD/automate/units/CConverterCoefOffset.cpp \
    $$PWD/automate/units/CConverterOffset.cpp \
    $$PWD/automate/units/CConverterOffsetCoef.cpp \
    $$PWD/automate/units/CConverterFactory.cpp \
    $$PWD/automate/units/CConverterUnknow.cpp \
    $$PWD/automate/units/CUnit.cpp \
    $$PWD/automate/units/IConverter.cpp \
    $$PWD/automate/variables/CVariableBool.cpp \
    $$PWD/automate/variables/CVariableFactory.cpp \
    $$PWD/automate/variables/CVariableFloat.cpp \
    $$PWD/automate/variables/CVariableInputBool.cpp \
    $$PWD/automate/variables/CVariableInputFloat.cpp \
    $$PWD/automate/variables/CVariableInputInt.cpp \
    $$PWD/automate/variables/CVariableInt.cpp \
    $$PWD/automate/variables/CVariableOutputBool.cpp \
    $$PWD/automate/variables/CVariableOutputFloat.cpp \
    $$PWD/automate/variables/CVariableOutputInt.cpp \
    $$PWD/automate/variables/CVariableString.cpp \
    $$PWD/automate/variables/CVariableUnknow.cpp \
    $$PWD/automate/variables/CVariableStream.cpp \
    $$PWD/automate/variables/CVariableMeasure.cpp \
    $$PWD/automate/variables/IVariable.cpp \
    $$PWD/automate/variables/IVariableInput.cpp \
    $$PWD/automate/variables/IVariableOuput.cpp \
    $$PWD/automate/variables/CVariableMutable.cpp \
    $$PWD/automate/organs/COrgan.cpp \
    $$PWD/automate/organs/COrganFactory.cpp \
    $$PWD/keyboards/CKeyboardButtonBase.cpp \
    $$PWD/keyboards/CKeyboardDialog.cpp \
    $$PWD/keyboards/CKeyboardLayoutUtils.cpp \
    $$PWD/keyboards/CKeyboardNormalButton.cpp \
    $$PWD/keyboards/CKeyboardSpecialButton.cpp \
    $$PWD/keyboards/CKeyboardWidget.cpp \
    $$PWD/keyboards/CNumericalKeyboardDialog.cpp \
    $$PWD/keyboards/CNumericalKeyboardWidget.cpp \
    $$PWD/updater/CUpdateDialog.cpp \
    $$PWD/updater/CUpdateManager.cpp \
    $$PWD/gui/widgets/CGenericItemSelector.cpp \
    $$PWD/gui/widgets/CGenericListDelegate.cpp \
    $$PWD/gui/widgets/CGenericListModel.cpp \
    $$PWD/gui/widgets/CLabelledToolButton.cpp \
    $$PWD/gui/widgets/CPushButton.cpp \
    $$PWD/gui/widgets/CScrollableWidget.cpp \
    $$PWD/gui/widgets/CScrollablePlainTextEdit.cpp \
    $$PWD/gui/widgets/CStatusLabel.cpp \
    $$PWD/gui/widgets/CStatusWidget.cpp \
    $$PWD/gui/widgets/CToolButton.cpp \
    $$PWD/gui/widgets/CVerticalButtonBar.cpp \
    $$PWD/gui/widgets/CSwitchButton.cpp \
    $$PWD/gui/widgets/CLedButton.cpp \
    $$PWD/gui/widgets/CLabelledToolButtonGrid.cpp \
    $$PWD/gui/widgets/CMessageBox.cpp \
    $$PWD/gui/widgets/CDialog.cpp \
    $$PWD/gui/widgets/CStepWidget.cpp \
    $$PWD/gui/widgets/CGenericVariablesEditor.cpp \
    $$PWD/gui/widgets/CGenericVariablesEditorWindow.cpp \
    $$PWD/gui/widgets/CGenericVariablesUIHandler.cpp \
    $$PWD/gui/widgets/CScrollablePagerWidget.cpp \
    $$PWD/gui/widgets/CProxyStyle.cpp \
    $$PWD/gui/panel/CAlarmsWindow.cpp \
    $$PWD/gui/panel/CPCDiagnosticTab.cpp \
    $$PWD/gui/panel/CPCHistogramTab.cpp \
    $$PWD/gui/panel/CPCMeasureTab.cpp \
    $$PWD/gui/panel/CPCPlusTab.cpp \
    $$PWD/gui/panel/CPCToolsTab.cpp \
    $$PWD/gui/panel/CPCWindow.cpp \
    $$PWD/gui/panel/IWindow.cpp \
    $$PWD/gui/measure/CMeasureMeasureTab.cpp \
    $$PWD/gui/measure/CMeasureStreamTab.cpp \
    $$PWD/gui/measure/CMeasureWindow.cpp \
    $$PWD/gui/tools/electrical-tests/CElectricalTests420Tab.cpp \
    $$PWD/gui/tools/electrical-tests/CElectricalTestsActuatorTab.cpp \
    $$PWD/gui/tools/electrical-tests/CElectricalTestsInputsTab.cpp \
    $$PWD/gui/tools/electrical-tests/CElectricalTestsPumpsTab.cpp \
    $$PWD/gui/tools/electrical-tests/CElectricalTestsRelaysTab.cpp \
    $$PWD/gui/tools/electrical-tests/CElectricalTestsWindow.cpp \
    $$PWD/gui/tools/options/COptionsWindow.cpp \
    $$PWD/gui/tools/options/COptionsOptionsTab.cpp \
    $$PWD/gui/tools/options/COptionsAutoCyclesTab.cpp \
    $$PWD/gui/tools/options/COptionsThresholdTab.cpp \
    $$PWD/gui/tools/options/COptionsDateTimeTab.cpp \
    $$PWD/gui/tools/log-files/CLogFilesWindow.cpp \
    $$PWD/gui/tools/history/CHistoryWindow.cpp \
    $$PWD/gui/tools/maintenance/CMaintenanceDiagnosticTab.cpp \
    $$PWD/gui/tools/maintenance/CMaintenanceMaintenanceTab.cpp \
    $$PWD/gui/tools/maintenance/CMaintenanceWindow.cpp \
    $$PWD/gui/IVariableMeasuresUIHandler.cpp \
    $$PWD/gui/IVariableUIHandler.cpp \
    $$PWD/gui/IVariableObjectDescriber.cpp \
    $$PWD/gui/IConfiguratorUIHandler.cpp \
    $$KPLOTTING_SRC_PWD/src/kplotaxis.cpp \
    $$KPLOTTING_SRC_PWD/src/kplotobject.cpp \
    $$KPLOTTING_SRC_PWD/src/kplotpoint.cpp \
    $$KPLOTTING_SRC_PWD/src/kplotwidget.cpp \
    $$PWD/graphics/CGraphicsWidget.cpp \
    $$PWD/graphics/CPlotObject.cpp \
    $$PWD/gui/IVariableMaintenanceUIHandler.cpp \
    $$PWD/gui/panel/CAboutWindow.cpp \
    $$PWD/automate/variables/CVariableOutputListVariables.cpp \
    $$PWD/automate/com/CComFactory.cpp \
    $$PWD/automate/com/CComUnknow.cpp \
    $$PWD/automate/cotautomate_debug.cpp \
    $$PWD/gui/cotgui_debug.cpp \
    $$PWD/gui/tools/configurator/CConfiguratorWindow.cpp \
    $$PWD/gui/tools/configurator/actions/CConfiguratorActionsTab.cpp \
    $$PWD/gui/tools/configurator/actions/CEditActionTab.cpp \
    $$PWD/gui/tools/configurator/actions/CEditActionTabUIHandler.cpp \
    $$PWD/gui/tools/configurator/actions/CEditActionWindow.cpp \
    $$PWD/gui/tools/configurator/actions/ConfiguratorActionsUIHandler.cpp \
    $$PWD/gui/tools/configurator/cycles/CConfiguratorCycleTab.cpp \
    $$PWD/gui/tools/configurator/cycles/CConfiguratorCycleTabUIHandler.cpp \
    $$PWD/gui/tools/configurator/cycles/CEditCycleTab.cpp \
    $$PWD/gui/tools/configurator/cycles/CEditCycleTabUIHandler.cpp \
    $$PWD/gui/tools/configurator/cycles/CEditCycleWindow.cpp \
    $$PWD/gui/tools/configurator/display/CConfiguratorDisplayTab.cpp \
    $$PWD/gui/tools/configurator/extensions/CConfiguratorExtensionsTab.cpp \
    $$PWD/gui/tools/configurator/extensions/CEditComTab.cpp \
    $$PWD/gui/tools/configurator/extensions/CEditExtensionWindow.cpp \
    $$PWD/gui/tools/configurator/extensions/CEditGeneralTab.cpp \
    $$PWD/gui/tools/configurator/extensions/CEditOrgansTab.cpp \
    $$PWD/gui/tools/configurator/hardware/CConfiguratorHardwareTab.cpp \
    $$PWD/gui/tools/configurator/network/CConfiguratorNetworkTab.cpp \
    $$PWD/gui/tools/configurator/sequencer/CConfiguratorSequencerTab.cpp \
    $$PWD/gui/tools/configurator/sequencer/ConfiguratorSequencerUIHandler.cpp \
    $$PWD/gui/tools/configurator/streams/CConfiguratorStreamsTab.cpp \
    $$PWD/gui/tools/configurator/streams/ConfiguratorStreamsUIHandler.cpp \
    $$PWD/gui/tools/configurator/variables/CConfiguratorVariablesTab.cpp \
    $$PWD/gui/tools/configurator/variables/CEditInBindsTab.cpp \
    $$PWD/gui/tools/configurator/variables/CEditInBindsUIHandler.cpp \
    $$PWD/gui/tools/configurator/variables/CEditOutBindsTab.cpp \
    $$PWD/gui/tools/configurator/variables/CEditOutBindsUIHandler.cpp \
    $$PWD/gui/tools/configurator/variables/CEditVariableTab.cpp \
    $$PWD/gui/tools/configurator/variables/CEditVariableTabUIHandler.cpp \
    $$PWD/gui/tools/configurator/variables/CEditVariableWindow.cpp \
    $$PWD/gui/tools/configurator/variables/ConfiguratorVariablesUIHandler.cpp \
    $$PWD/gui/IScrollableUIWidget.cpp \
    $$PWD/gui/IScrollablePlainTextEdit.cpp \
    $$PWD/gui/tools/configurator/IConfiguratorEditWindow.cpp \
    $$PWD/gui/tools/configurator/steps/CStepWidgetUIHandler.cpp \
    $$PWD/gui/tools/configurator/steps/CEditStepListTab.cpp \
    $$PWD/gui/StyleRepository.cpp \
    $$PWD/automate/actions/CActionCmdDigitalOutput.cpp \
    $$PWD/automate/actions/CActionTest.cpp \
    $$PWD/automate/CScheduler.cpp \
    $$PWD/automate/actions/CActionAcquisitionCitNpoc.cpp \
    $$PWD/automate/actions/CActionDCEngine.cpp \
    $$PWD/automate/actions/CActionRewriteOutput.cpp \
    $$PWD/automate/CThreadDiag.cpp \
    $$PWD/gui/widgets/CClickableLabel.cpp\
    $$PWD/automate/units/CConverterCrossProduct.cpp \
    $$PWD/gui/tools/initial-tests/CInitialTestWindow.cpp \
    $$PWD/gui/widgets/CDialogMaintenance.cpp \
    $$PWD/automate/actions/CActionCalibrationCalcul.cpp \
    $$PWD/automate/variables/CVariableAlarm.cpp \
    $$PWD/automate/actions/CActionCmd420.cpp \
    $$PWD/gui/tools/screenshot/CDialogScreenShots.cpp \
    $$PWD/automate/actions/CActionSum.cpp \
    $$PWD/automate/actions/CActionFindClosestFromReference.cpp \
    $$PWD/automate/actions/CActionFindBiggerValue.cpp \
    $$PWD/gui/tools/electrical-tests/CElectricalTestsSolenoidsTab.cpp

DISTFILES +=

