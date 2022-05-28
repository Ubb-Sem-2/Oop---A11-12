#pragma once
#include <QtWidgets/QWidget>
#include "Service.h"
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include "UserService.h"
#include <QtWidgets/QListWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include "Validator.h"

class TutorialListModel : public QAbstractListModel
{
private:
	Repository& repo;
public:
	TutorialListModel(Repository& repo) : repo(repo) {};

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;


};

class GUI : public QWidget
{
private:
	Service& service;
	UserService& userService;
	TutValidator& validator;
	Repository& repository;
	void initGUI();
	QLabel* titleWidget;
	QPushButton* adminButton;
	QPushButton* userButton;
	void showAdmin();
	void showUser();
	void connectSignalsAndSlots();
public:
	GUI(Service& service, UserService& userserv, TutValidator& validator1, Repository& repo);
	~GUI() override;

};

class AdminGUI : public QWidget
{
private:
	Service& service;
	TutValidator& validator;
	Repository& repository;
	void initAdminGUI();
	QLabel* titleWidget;
	QListWidget* tutorialsListWidget;
	QLineEdit* titleLineEdit, *presenterLineEdit, *minutesLineEdit, *secondsLineEdit, *likesLineEdit, *sourceLineEdit;
	QPushButton* addButton, *deleteButton, *updateButton, *chartButton;
	TutorialListModel* listModel;

	void populateList();
	void connectSignalsAndSlots();
	int getSelectedIndex() const;
	void addTutorial();
	void deleteTutorial();
	void updateTutorial();
	void displayChart();

	QWidget* chartWindow;

public:
	AdminGUI(QWidget* parent, Service& serv, TutValidator& valid, Repository& repo);
	~AdminGUI() override;

};



class UserGUI : public QWidget
{
private:
	Service& service;
	UserService& userService;
	TutValidator& validator;
	void initUserGUI();
	QLabel* titleWidget;
	QListWidget* tutorialsLisWidget, *watchListWidget;
	QLineEdit *titleLineEdit, *presenterLineEdit, *minutesLineEdit, *secondsLineEdit, *likesLineEdit, *sourceLineEdit, *filterPresenterLineEdit;
	QPushButton* tutGivenPresenterButton, *deleteTutWLButton, * seeListButton, *filterButton;
	QRadioButton* csvButton, * htmlButton;
	bool repoTypeSelected;
	bool filtered;
	void populateTutorialsList();
	void populateWatchList();
	void connectSignalsAndSlots();
	int getSelectedIndex() const;
	void addTutorial();
	void filterTutorials();

	QPushButton* nextButton, * saveButton, * openButton, * deleteButton, * showButton;
	void userNext();
	void userDelete();



public:
	UserGUI(QWidget* parent, Service& serv, UserService& userServ, TutValidator& valid);
	~UserGUI() override;

};


/*
class UserGUI : public QWidget
{
	Q_OBJECT
private:
	Service* service;
	WatchListRepo* watchlist;
public:
	UserGUI(Service* serv, WatchListRepo* wl, QWidget* parent = Q_NULLPTR);
	~UserGUI();
	void userInterface();
	void printTutorial(Tutorial* tut);
private slots:
	void userSearch();
	void userAdd();
	void userNext();
	void userSave();
	void userOpen();
	void userDelete();
	void userShow();

	
};
*/