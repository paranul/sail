#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <vector>

static constexpr unsigned int MAX_COMPONENTS = 32;


//Bitset is used to create a signature for the components
// std::bitset<MAX_COMPONENTS> foo;

class IComponent
{

protected:
    static inline uint32_t nextID  = 0;
};

//used to store the actual data e.g: TransformComponent, SpriteComponent, BoxColliderComponent
//Every Component needs to have a uniqueID so that we can later check this with a 
//RequireComponent<componentType>() function
class Component
{

};

class Entity
{

public:
    Entity(int id) 
    : 
        m_id(id) 
    {

    }

    int GetID() const; //const at end = does not modify any data members

public:
    //can do Entity entity == Entity other
    bool operator ==(const Entity& rhs) const
    {
        return (this->m_id == rhs.m_id);
    }
    bool operator !=(const Entity rhs) const
    {
        return (this->m_id != rhs.m_id);
    }
    Entity& operator =(const Entity& rhs) = default;


private:
    int m_id;

};




//Does the logic on the components e.g: MovementSystem, AnimationSystem
class System
{

public:
    System() = default;
    ~System() = default;

    void AddEntityToSystem(Entity entity);
    void RemoveEntityFromSystem(Entity entity);
    std::vector<Entity> GetSystemEntities() const;
    std::bitset<MAX_COMPONENTS>& GetComponentSignature() const;

private:
    std::bitset<MAX_COMPONENTS> m_componentSignature;
    std::vector<Entity> m_entities;

    template<typename TComponent> void RequiredComponent()
    {

        m_componentSignature.set(/*componentID*/);
    }
};



//Pool Class info:
template <typename T>
class Pool
{

public:


private:

};



//Registry class info:
//vector index -> component id
//pool index -> entity id
//std::vector<Pool*> componentPools;

class Registry
{

public:



private:
    //Keeps track of the number of entities in the scene, adds systems, and components;
    uint32_t m_numofEntities = 0;

    //vector of component pools, each pool contains all the data of a certain component type
    //TODO: std::vector<Pool*> m_componentPools;

};



#endif