#ifndef PARAMETERSLIDER_H
#define PARAMETERSLIDER_H

#include <QWidget>

namespace Ui {
    class ParameterSlider;
}

class ParameterSlider : public QWidget
{
Q_OBJECT
public:
    ParameterSlider(QWidget* parent);
    virtual ~ParameterSlider();

    void setValues(const QStringList& values);

    void setSliderValue(int value);
    int sliderValue() const;

public slots:
    void slotSliderChanged(int value);
//     void slotTextChanged();

private:
    Ui::ParameterSlider* m_ui;

    QStringList m_values;
};

#endif // PARAMETERSLIDER_H
