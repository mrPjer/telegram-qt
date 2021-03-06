#include "CChatInfoModel.hpp"

#include <QDebug>

CChatInfoModel::CChatInfoModel(QObject *parent) :
    QAbstractTableModel(parent)
{

}

QVariant CChatInfoModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal) {
        return QVariant();
    }

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    switch (section) {
    case Id:
        return tr("Id");
    case Title:
        return tr("Title");
    case ParticipantsCount:
        return tr("Participants");
    default:
        break;
    }

    return QVariant();
}

QVariant CChatInfoModel::data(const QModelIndex &index, int role) const
{
    int section = index.column();
    int chatIndex = index.row();

    if ((role != Qt::DisplayRole) && (role != Qt::EditRole)) {
        return QVariant();
    }

    if (chatIndex >= rowCount()) {
        return QVariant();
    }

    switch (section) {
    case Id:
        return m_chats.at(chatIndex).id;
    case Title:
        return m_chats.at(chatIndex).title;
    case ParticipantsCount:
        return m_chats.at(chatIndex).participantsCount;
    default:
        break;
    }

    return QVariant();
}

void CChatInfoModel::addChat(int id)
{
    beginInsertRows(QModelIndex(), m_chats.count(), m_chats.count());
    m_chats.append(TelegramNamespace::GroupChat(id));
    endInsertRows();
}

bool CChatInfoModel::haveChat(quint32 id)
{
    for (int i = 0; i < m_chats.count(); ++i) {
        if (m_chats.at(i).id == id) {
            return true;
        }
    }
    return false;
}

void CChatInfoModel::setChat(const TelegramNamespace::GroupChat &chat)
{
    for (int i = 0; i < m_chats.count(); ++i) {
        if (m_chats.at(i).id != chat.id) {
            continue;
        }

        m_chats[i] = chat;
        emit dataChanged(index(i, 0), index(i, ColumnsCount - 1));
        return;
    }

    qDebug() << Q_FUNC_INFO << "id" << chat.id << "not found.";
}
