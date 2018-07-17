#ifndef APPMODEL_H
#define APPMODEL_H

#include "Controller/appcontroller.h"

/*
    Model:
        - Data storage, integrity, queries
        - The model does NOT depend on the controller or the view
        - The model represents the data, and does nothing else - Golden rule of MVC
        - MVC makes model classes reusable without modification
*/

class AppModel
{
public:
    AppModel();
};

#endif // APPMODEL_H
