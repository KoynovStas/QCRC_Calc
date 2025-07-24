import QtQuick 2.8
import QtQuick.Controls 2.1




SpinBox {
    id: spinBox


    rightPadding: 20
    leftPadding: 20

    editable: true

    contentItem: TextInput {
        z: 2

        text: spinBox.textFromValue(spinBox.value, spinBox.locale)

        font: spinBox.font
        color: "#21be2b"
        selectionColor: "#21be2b"
        selectedTextColor: "#ffffff"
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter

        readOnly: !spinBox.editable

        validator: RegExpValidator {
            regExp: /\d{1,2}/
        }

        inputMethodHints: Qt.ImhDigitsOnly
    }


    valueFromText: function(text, locale) { return Number.fromLocaleString(locale, text); }
    textFromValue: function(value, locale) { return Number(value).toLocaleString(locale, 'd', 0); }


    validator: IntValidator {
        bottom: Math.min(spinBox.from, spinBox.to)
        top: Math.max(spinBox.from, spinBox.to)
    }
}
