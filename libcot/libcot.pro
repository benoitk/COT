TEMPLATE = lib
TARGET = cotwidgets
CONFIG *= c++11
QT *= widgets

DEFINES *= COTWIDGETS_BUILD_COTWIDGETS_LIB

DEFINES *= "COT_JSON_FILE=\\\"$$PWD/save.json\\\""

DESTDIR = ../lib

INCLUDEPATH *= \
    . \
    gui \
    automate/variables \
    automate \
    automate/com \
    automate/cycles \
    automate/actions \
    automate/units

DEPENDPATH *= \
    . \
    gui \
    automate/variables \
    automate \
    automate/com \
    automate/cycles \
    automate/actions \
    automate/units

RESOURCES *= \
    resources/cot-resources.qrc

FORMS *= \
    gui/cotversion1.ui

HEADERS *= \
    automate/CAutomate.h \
    automate/CControlerAutomate.h \
    automate/CControlerCycle.h \
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
    gui/cotversion1.h \
    keyboards/keyboardbuttonbase.h \
    keyboards/keyboarddialog.h \
    keyboards/numericalkeyboarddialog.h \
    keyboards/keyboardspecialbutton.h \
    keyboards/keyboardnormalbutton.h \
    keyboards/keyboardlayoututils.h \
    keyboards/keyboardwidget.h \
    keyboards/numericalkeyboardwidget.h

SOURCES *= \
    automate/CAutomate.cpp \
    automate/CControlerAutomate.cpp \
    automate/CControlerCycle.cpp \
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
    gui/cotversion1.cpp \
    keyboards/keyboardbuttonbase.cpp \
    keyboards/keyboarddialog.cpp \
    keyboards/numericalkeyboarddialog.cpp \
    keyboards/keyboardspecialbutton.cpp \
    keyboards/keyboardnormalbutton.cpp \
    keyboards/keyboardlayoututils.cpp \
    keyboards/keyboardwidget.cpp \
    keyboards/numericalkeyboardwidget.cpp

DISTFILES *= \
    save.json \
    utf-8-converter.sh
