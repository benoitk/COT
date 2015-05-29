#include "IVariable.h"

int IVariable::FLOAT_PRECISION = 3;

IVariable::IVariable(QObject *parent)
    : QObject(parent)
{

}

QString IVariable::typeToString(variableType type)
{
    switch (type) {
        case type_bool:
            return tr("Boolean");

        case type_float:
            return tr("Float");

        case type_int:
            return tr("Integer");

        case type_string:
            return tr("String");

        case type_stream:
            return tr("Stream");

        case type_measure:
            return tr("Measure");

        case type_list_variables:
            return tr("Variables list");

        case type_mutable:
            return tr("Mutable");

        case type_unknow:
            return tr("Unknown");
    }

    return QStringLiteral("**unhandled variable type**");
}

QString IVariable::organTypeToString(VariableOrganType type)
{
    switch (type) {
        case VariableOrganTypeNone:
            return tr("None");

        case VariableOrganTypeInput:
            return tr("Input");

        case VariableOrganTypeOutput:
            return tr("Output");
    }

    return QStringLiteral("**unhandled organ type**");
}

void IVariable::setAddress(int address)
{
    Q_UNUSED(address);
}
