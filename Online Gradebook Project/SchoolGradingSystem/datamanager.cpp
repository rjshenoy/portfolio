#include "datamanager.h"

// instantiate the dataManager instance
DataManager* DataManager::dataManager = nullptr;

DataManager::DataManager()
{

}

DataManager* DataManager::GetInstance()
{
    if (dataManager == nullptr) {
        dataManager = new DataManager();
    }
    return dataManager;
}
