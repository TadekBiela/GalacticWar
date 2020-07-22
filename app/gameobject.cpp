#include "gameobject.hpp"

GameObject::GameObject(game_object_type type)
    : m_type(type)
{

}

game_object_type GameObject::getType() const
{
    return m_type;
}
