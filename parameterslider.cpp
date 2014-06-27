#include "parameterslider.h"
#include "ui_parameterslider.h"

ParameterSlider::ParameterSlider(QWidget* parent)
    : QWidget(parent)
    , m_ui(new Ui::ParameterSlider)
{
    m_ui->setupUi(this);

    m_ui->slider->setTracking(true);
    setEnabled(false);
    connect(m_ui->slider, SIGNAL(valueChanged(int)), this, SLOT(slotSliderChanged(int)));

    m_ui->lineEdit->setReadOnly(true);
//     connect(m_ui->lineEdit, SIGNAL(textEdited(QString)), this, SLOT(slotTextChanged(QString)));
}

ParameterSlider::~ParameterSlider()
{
}

void ParameterSlider::setValues(const QStringList& values)
{
    m_values = values;

    setEnabled(m_values.size() > 1);

    if (!m_values.isEmpty()) {
        m_ui->slider->setRange(0, m_values.size() - 1);
        setSliderValue(0);
    }
}

void ParameterSlider::setSliderValue(int value)
{
    m_ui->slider->setValue(value);
    slotSliderChanged(value);
}

int ParameterSlider::sliderValue() const
{
    return m_ui->slider->value();
}

void ParameterSlider::slotSliderChanged(int value)
{
    Q_ASSERT(value >= 0 && value < m_values.size());
    m_ui->lineEdit->setText(m_values[value]);
}
