#include "Assignment11.h"
#include <QtWidgets/QApplication>
#include "Gui.h"
#include "Validator.h"
#include "Repository.h"
#include "Service.h"
#include <crtdbg.h>
#include "UserService.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::vector<Tutorial> adminRepoVector;
    adminRepoVector.reserve(10);
    std::string filename= "D:\\FACULTATE\\Materiale facultate 2021-2022\\1.2\\Object Oriented Programming\\Assignments\\A8-9\\A8-9\\A8-9\\Tutorials.txt";
    Repository repo(filename);
    repo.initialiseRepo();
    Service service(repo);
    UserService userService(repo);
    TutValidator validator;
    GUI gui(service, userService, validator, repo);
    gui.show();

    //Assignment11 w;
    //w.show();
    return a.exec();
}
