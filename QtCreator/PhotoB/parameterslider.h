#ifndef PARAMETERSLIDER_H
#define PARAMETERSLIDER_H

#include <QWidget>
#include <QMap>

namespace Ui {
    class ParameterSlider;
}

class ParameterSlider : public QWidget
{
Q_OBJECT

    typedef std::vector<int> vint;

    Ui::ParameterSlider* m_ui;
    vint m_values;
    QStringList m_labels;

public:
    ParameterSlider(QWidget* parent);
    virtual ~ParameterSlider();

    void setValues(const vint& values, const QStringList& labels);
    void setSliderPosition(int pos);

    int sliderValue() const;
    int sliderPosition() const;

public slots:
    void slotSliderChanged(int pos);
};

#endif // PARAMETERSLIDER_H
