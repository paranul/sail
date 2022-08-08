
#include "ECS.h"

//#include <algorithm> //Might be necessary on some compilers for std::remove_if

int Entity::GetID() const
{
    return m_id;
}

void System::AddEntityToSystem(Entity entity)
{
    m_entities.push_back(entity);
}

void System::RemoveEntityFromSystem(Entity entity)
{

    //Lambda Function shortway, 
    //erase works with iterators (So can later be changed to other types of container e.g map, while for loop will not )
    //std::remove_if(iterator.begin(), iterator.end(), lambda function here)
    //Note std::remove_if does reshuffle everything to fill in the gaps of removed items (Erase-Remove Idiom) and doesnt actually remove anything it returns
    //the iterator to the first one that didnt match the lambda bool value

    //lambda = [&entity](Entity other)
    //{ 
    //     return entity.GetID() == other.GetID(); 
    //};

    m_entities.erase(std::remove_if( m_entities.begin(), m_entities.end(), [&entity](Entity other)
    { 
        return entity.GetID() == other.GetID(); 
    } ));

    // for(int i = 0; i < m_entities.size(); i++)
    // {
    //     if(entity.GetID() == m_entities[i].GetID())
    //     {
    //         m_entities.erase(m_entities.begin() + i);
    //     }
    // }

}
