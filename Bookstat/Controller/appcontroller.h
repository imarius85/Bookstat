#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include "View/appview.h"
#include "Model/appmodel.h"

/*
    Controller:
        - Receive, interpret & validate input
        - Create / Update views
        - Query / Modify models
        - In some cases, the controller and the view are the same object
*/

class AppController
{
public:
    AppController();
};

#endif // APPCONTROLLER_H
