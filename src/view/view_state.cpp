#include "../../include/app_view.h"

namespace hmi
{

    ScreenState::ScreenState(qreal x, qreal y, qreal z,
                             qreal width, qreal height, bool opacity,
                             bool enable, bool visible) :
        m_x(x),
        m_y(y), m_z(z),
        m_width(width), m_height(height), m_opacity(opacity),
        m_enabled(enable), m_visible(visible) {
    }
    ScreenState::~ScreenState() {
    }

    void ScreenState::setX(qreal value) {
        if (value == m_x) return;
        m_x = value;
        emit xChanged();
    }
    void ScreenState::setY(qreal value) {
        if (value == m_y) return;
        m_y = value;
        emit yChanged();
    }
    void ScreenState::setZ(qreal value) {
        if (value == m_z) return;
        m_z = value;
        emit zChanged();
    }
    void ScreenState::setWidth(qreal value) {
        if (value == m_width) return;
        m_width = value;
        emit widthChanged();
    }
    void ScreenState::setHeight(qreal value) {
        if (value == m_height) return;
        m_height = value;
        emit heightChanged();
    }
    void ScreenState::setOpacity(qreal value) {
        if (value == m_opacity) return;
        m_opacity = value;
        emit opacityChanged();
    }
    void ScreenState::setEnabled(bool value) {
        if (value == m_enabled) return;
        m_enabled = value;
        emit enabledChanged();
    }
    void ScreenState::setVisible(bool value) {
        if (value == m_visible) return;
        m_visible = value;
        emit visibleChanged();
    }

    void ScreenState::setHeaderContainer(const QString &value) {
        if (value == m_containerSource.header) return;
        m_containerSource.header = value;
        emit headerContainerChanged();
    }

    void ScreenState::setFooterContainer(const QString &value) {
        if (value == m_containerSource.footer) return;
        m_containerSource.footer = value;
        emit footerContainerChanged();
    }

    void ScreenState::setLeftContainer(const QString &value) {
        if (value == m_containerSource.left) return;
        m_containerSource.left = value;
        emit leftContainerChanged();
    }

    void ScreenState::setRightContainer(const QString &value) {
        if (value == m_containerSource.right) return;
        m_containerSource.right = value;
        emit rightContainerChanged();
    }

    qreal ScreenState::x() const { return m_x; }
    qreal ScreenState::y() const { return m_y; }
    qreal ScreenState::z() const { return m_z; }
    qreal ScreenState::width() const { return m_width; }
    qreal ScreenState::height() const { return m_height; }
    qreal ScreenState::opacity() const { return m_opacity; }
    bool ScreenState::isEnabled() const { return m_enabled; }
    bool ScreenState::isVisible() const { return m_visible; }
    QString ScreenState::getHeaderContainer() const { return m_containerSource.header; }
    QString ScreenState::getFooterContainer() const { return m_containerSource.footer; }
    QString ScreenState::getLeftContainer() const { return m_containerSource.left; }
    QString ScreenState::getRightContainer() const { return m_containerSource.right; }

} // namespace hmi
