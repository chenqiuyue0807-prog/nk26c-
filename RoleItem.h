#ifndef ROLEITEM_H
#define ROLEITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPainter>

// 角色类型
enum class RoleType {
    Hunter,      // 监管者（厂长）
    Doctor,      // 医生
    Mechanic,    // 机械师
    AirForce     // 空军
};

// 角色状态
enum class RoleState {
    Idle,        // 空闲
    Moving,      // 移动中
    Interacting, // 交互中（破译、治疗、开门、救助等）
    Stunned,     // 眩晕
    Dead         // 已淘汰
};

class RoleItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit RoleItem(RoleType type, QObject *parent = nullptr);

    // 基础属性
    RoleType roleType() const { return m_type; }
    int health() const { return m_health; }
    void setHealth(int health);
    qreal speed() const { return m_speed; }
    void setSpeed(qreal speed) { m_speed = speed; }

    // 状态控制
    RoleState state() const { return m_state; }
    void setState(RoleState state);
    bool isInteracting() const { return m_state == RoleState::Interacting; }
    bool isDead() const { return m_state == RoleState::Dead; }

    // 移动控制（用于玩家和 AI）
    void setMoveDirection(qreal dx, qreal dy);
    void stopMoving();

    // 每帧更新位置（由 GameScene 调用）
    void updatePosition(const QRectF &bounds);

    // 受伤减速效果（PDF 要求：受伤后移速降低 20%）
    void applyHurtSpeedDebuff();
    void removeHurtSpeedDebuff();

signals:
    void healthChanged(int newHealth);
    void stateChanged(RoleState newState);

private:
    RoleType m_type;
    RoleState m_state;
    int m_health;
    qreal m_speed;
    qreal m_baseSpeed;      // 基础速度（用于受伤减速恢复）
    bool m_isHurt;           // 是否处于受伤状态

    // 移动方向（归一化向量）
    qreal m_moveDx;
    qreal m_moveDy;

    // 根据角色类型初始化外观和属性
    void setupByType();
};

#endif // ROLEITEM_H