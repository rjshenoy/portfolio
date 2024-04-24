
#ifndef DATAMANAGER_H
#define DATAMANAGER_H


/* Uses Singleton Design Pattern */

class DataManager
{
    public:

        // Can't clone
        DataManager(DataManager &other) = delete;
        // Can't instantiate through = operator
        void operator=(const DataManager &other) = delete;
        // Singleton get instance method
        static DataManager *GetInstance();

    private:

        // Instance:
        static DataManager* dataManager;

        // Make constructor Private
        DataManager();

};

#endif // DATAMANAGER_H
