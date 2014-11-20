#include "parameterslider.h"
#include "ui_parameterslider.h"

ParameterSlider::ParameterSlider(QWidget* parent)
    : QWidget(parent)
    , m_ui(new Ui::ParameterSlider)
{
    m_ui->setupUi(this);
    m_ui->slider->setTracking(true);
    m_ui->lineEdit->setReadOnly(true);
    setEnabled(false);

    connect(m_ui->slider, SIGNAL(valueChanged(int)), this, SLOT(slotSliderChanged(int)));
}

ParameterSlider::~ParameterSlider()
{
}

void ParameterSlider::setValues(const vint& values, const QStringList& labels)
{
    Q_ASSERT(values.size() == labels.size());
    m_values = values;
    m_labels = labels;

    setEnabled(m_values.size() > 1);

    if (!m_values.empty()) {
        m_ui->slider->setRange(0, m_values.size() - 1);
        setSliderPosition(0);
    }
}

void ParameterSlider::setSliderPosition(int pos)
{
    m_ui->slider->setValue(pos);
    slotSliderChanged(pos);
}

int ParameterSlider::sliderPosition() const
{
    return m_ui->slider->value();
}

int ParameterSlider::sliderValue() const
{
    return m_values[m_ui->slider->value()];
}

void ParameterSlider::slotSliderChanged(int pos)
{
    Q_ASSERT(pos >= 0 && pos < m_values.size());
    m_ui->lineEdit->setText(m_labels[pos]);
}
